/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:00:37 by deladia           #+#    #+#             */
/*   Updated: 2020/01/28 14:53:00 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_create_buffer(t_cl *cl, t_scene *scene)
{
	cl_int		ret;

	if ((cl->memobjs[0] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * WIDTH * HEIGHT, NULL, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((cl->memobjs[1] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_cam), &scene->cam, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((cl->memobjs[2] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * 6, scene->object, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((cl->memobjs[3] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * 1, scene->light, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((cl->memobjs[4] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(cl_int) * scene->texture_length,
			NULL, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((cl->memobjs[5] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(cl_int) * scene->texture_cnt * 3,
			NULL, &ret)) && ret != 0)
		// 
		ft_error("LOL");
}

static void		print_build_error(t_cl *cl, cl_int ret, size_t log_size)
{
	char		*log;

	clGetProgramBuildInfo(cl->program, cl->device_id,
						CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = (char*)malloc(log_size);
	clGetProgramBuildInfo(cl->program, cl->device_id,
						CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	ft_putstr("build program - ERROR(");
	ft_putnbr(ret);
	ft_putstr(")\n");
	ft_putendl(log);
	exit(-1);
}

static void		create_cl_1(t_cl *cl, t_scene *scene)
{
	cl_int		ret;
	size_t		log_size;

	if ((cl->program = clCreateProgramWithSource(cl->context, cl->count_files,
						(const char **)cl->program_source,
						(const size_t *)cl->program_size, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((ret = clBuildProgram(cl->program, 1, &cl->device_id,
						"-DOPENCL___ -I include/ ", NULL, NULL)) != 0)
		print_build_error(cl, ret, log_size);
	if ((cl->kernel = clCreateKernel(cl->program, "RT", &ret)) && ret != 0)
		// 
		ft_error("LOL");
	cl->global_work_size[0] = WIDTH;
	cl->global_work_size[1] = HEIGHT;
	cl->local_work_size[0] = 16;
	cl->local_work_size[1] = 16;
	cl_create_buffer(cl, scene);
}

int				create_cl(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	int			ret;

	if ((ret = clGetPlatformIDs(1, &cl->platform_id, &cl->ret_num_platforms))
		!= 0)
		// 
		ft_error("LOL");
	if ((ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
							&cl->device_id, &cl->ret_num_devices)) != 0)
		// 
		ft_error("LOL");
	if ((cl->context = clCreateContext(NULL, 1, &cl->device_id,
									NULL, NULL, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	if ((cl->cmd_queue = clCreateCommandQueue(cl->context, cl->device_id,
											0, &ret)) && ret != 0)
		// 
		ft_error("LOL");
	create_cl_1(cl, scene);
	set_opencl_arg(cl, sdl, scene);
	return (0);
}

t_cl			*init_opencl(void)
{
	t_cl		*opencl;

	opencl = (t_cl *)ft_memalloc(sizeof(t_cl));
	opencl->files = init_files_cl();
	return (opencl);
}
