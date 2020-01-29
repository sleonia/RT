/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:00:37 by deladia           #+#    #+#             */
/*   Updated: 2020/01/29 02:45:23 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_arg_1(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	int		ret;

	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
									sizeof(cl_int) * HEIGHT * WIDTH, (cl_int *)sdl->pixels, 0, NULL,
									NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[1], CL_TRUE, 0,
									sizeof(t_cam), &scene->cam, 0, NULL,
									NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[2], CL_TRUE, 0,
									sizeof(t_object) * scene->count_objects, scene->object, 0, NULL,
									NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[3], CL_TRUE, 0,
									sizeof(t_light) * scene->count_lights, scene->light, 0, NULL,
									NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[4], CL_TRUE, 0, 
									sizeof(cl_int) * scene->texture_length, (cl_int *)scene->texture, 0, NULL, 
									NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[5], CL_TRUE, 0, 
									sizeof(cl_int) * scene->texture_cnt * 3, (cl_int *)scene->texture_param, 0, NULL, 
									NULL)) != 0)
		func_error(-10);
	// не добавляется локал ворк сайз
	if ((ret = clEnqueueNDRangeKernel(cl->cmd_queue, cl->kernel, 2, NULL, cl->global_work_size, cl->local_work_size, 0, NULL, NULL)) != 0)
		func_error(-11);
	if ((ret = clEnqueueReadBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
								   HEIGHT * WIDTH * sizeof(cl_int), (cl_int *)sdl->pixels, 0, NULL,
								   NULL)) != 0)
		func_error(-12);
	return (0);
}

int		set_arg(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	cl_int	ret;
	int		side_x;
	int		side_y;

	side_x = WIDTH;
	side_y = HEIGHT;
	ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->memobjs[0]);
	ret |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->memobjs[1]);
	ret |= clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->memobjs[2]);
	ret |= clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->memobjs[3]);
	ret |= clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->memobjs[4]);
	ret |= clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->memobjs[5]);
	ret |= clSetKernelArg(cl->kernel, 6, sizeof(cl_int), &scene->count_objects);
	ret |= clSetKernelArg(cl->kernel, 7, sizeof(cl_int), &scene->count_lights);
	ret |= clSetKernelArg(cl->kernel, 8, sizeof(cl_int), &scene->skybox_id);
	if (ret != 0)
		func_error(-9);
	set_arg_1(cl, sdl, scene);
	return (0);
}

int		create_cl_1(t_cl *cl, t_scene *scene)
{
	cl_int		ret;
	char	*log;
	size_t	log_size;

	if ((cl->program = clCreateProgramWithSource(cl->context, cl->count_files, (const char **)
			cl->program_source, (const size_t *)cl->program_size, &ret))
		&& ret != 0)
		func_error(-6);
	if ((ret = clBuildProgram(cl->program, 1, &cl->device_id, "-DOPENCL___ -I include/ ", NULL, NULL))
		!= 0)
	{
		if (ret != 0)
		{
			clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
			log = (char*)malloc(log_size);
			clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
			printf("build program - ERROR (%d)\n", ret);
			printf("%s\n", log);
			exit(-1);
		}
	}
	if ((cl->kernel = clCreateKernel(cl->program, "RT", &ret)) && ret != 0)
		func_error(-8);
	cl->global_work_size[0] = WIDTH;
	cl->global_work_size[1] = HEIGHT;
	cl->local_work_size[0] = 16;
	cl->local_work_size[1] = 16;
	if ((cl->memobjs[0] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(cl_int) * WIDTH * HEIGHT, NULL, &ret)) && ret != 0)
		func_error(-5);
	if ((cl->memobjs[1] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_cam), &scene->cam, &ret)) && ret != 0)
		func_error(-5);
	if ((cl->memobjs[2] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_object) * scene->count_objects, scene->object, &ret)) && ret != 0)
		func_error(-5);
	if ((cl->memobjs[3] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * scene->count_lights, scene->light, &ret)) && ret != 0)
		func_error(-5);
	if ((cl->memobjs[4] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(cl_int) * scene->texture_length, NULL, &ret)) && ret != 0)
		func_error(-5);
	if ((cl->memobjs[5] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(cl_int) * scene->texture_cnt * 3, NULL, &ret)) && ret != 0)
		func_error(-5);
	return (0);
}

int		create_cl(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
    int     ret;

    if ((ret = clGetPlatformIDs(1, &cl->platform_id, &cl->ret_num_platforms))
        != 0)
        func_error(-1);
    if ((ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
                              &cl->device_id, &cl->ret_num_devices)) != 0)
        func_error(-2);
    if ((cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL,
                                       &ret)) && ret != 0)
        func_error(-3);
    if ((cl->cmd_queue = clCreateCommandQueue(cl->context, cl->device_id, 0,
                                              &ret)) && ret != 0)
        func_error(-4);
    create_cl_1(cl, scene);
	set_arg(cl, sdl, scene);
	return (0);
}