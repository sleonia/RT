/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_blur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:15:57 by deladia           #+#    #+#             */
/*   Updated: 2020/02/03 15:39:16 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_create_buffer_blur_1(t_cl *cl, t_scene *scene)
{
	cl_int		ret;

	ret = 0;
	if ((cl->memobjs[3] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * scene->count_lights, scene->light, &ret))
			&& ret != 0)
		ft_error("clCreateBuffer");
	if ((cl->memobjs[4] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(cl_int) * scene->texture_length, NULL, &ret)) && ret != 0)
		ft_error("clCreateBuffer");
	if ((cl->memobjs[5] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(cl_int) * scene->texture_cnt * 3,
			NULL, &ret)) && ret != 0)
		ft_error("clCreateBuffer");
}

static void		cl_create_buffer_blur(t_cl *cl, t_scene *scene)
{
	cl_int		ret;

	ret = 0;
	if ((cl->memobjs[0] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * WIDTH * HEIGHT, NULL, &ret)) && ret != 0)
		ft_error("clCreateBuffer");
	if ((cl->memobjs[1] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_cam), &scene->cam, &ret)) && ret != 0)
		ft_error("clCreateBuffer");
	if ((cl->memobjs[2] = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * scene->count_objects, scene->object, &ret))
			&& ret != 0)
		ft_error("clCreateBuffer");
	cl_create_buffer_blur_1(cl, scene);
}

void			create_cl_blur(t_cl *cl, t_scene *scene)
{
	cl_int		ret;
	size_t		log_size;

	//free cl->program_source;
	//free cl->program_size;
	read_kernel(cl, files_cl);
	if ((cl->program = clCreateProgramWithSource(cl->context, cl->count_files,
						(const char **)cl->program_source,
						(const size_t *)cl->program_size, &ret)) && ret != 0)
		ft_error("clCreateProgramWithSource");
	if ((ret = clBuildProgram(cl->program, 1, &cl->device_id,
						"-DOPENCL___ -I include/ ", NULL, NULL)) != 0)
		print_build_error(cl, ret, log_size);
	if ((cl->kernel = clCreateKernel(cl->program, "blur", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	cl_create_buffer_blur(cl, scene);
}
