/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_blur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:15:57 by deladia           #+#    #+#             */
/*   Updated: 2020/02/05 22:36:43 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_arg_blur(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	int		ret;
	int		*output;

	output = (int *)ft_memalloc(sizeof(int) * HEIGHT * WIDTH);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
								sizeof(cl_int) * HEIGHT * WIDTH,
								(cl_int *)sdl->sur->pixels, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[1], CL_TRUE, 0,
								sizeof(cl_int) * HEIGHT * WIDTH,
								(cl_int *)output, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueNDRangeKernel(cl->cmd_queue, cl->kernel, 2, NULL,
			cl->global_work_size, cl->local_work_size, 0, NULL, NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueReadBuffer(cl->cmd_queue, cl->memobjs[1], CL_TRUE, 0,
									HEIGHT * WIDTH * sizeof(cl_int),
									(cl_int *)output, 0, NULL,
									NULL)) != 0)
		func_error(-12);
	sdl->sur->pixels = ft_memcpy(sdl->sur->pixels, output, HEIGHT * WIDTH);
	free(output);
}

static int		set_opencl_arg_for_blur(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	cl_int		ret;

	ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->memobjs[0]);
	ret |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->memobjs[1]);
	if (ret != 0)
		func_error(-9);
	set_arg_blur(cl, sdl, scene);
	return (0);
}

static void		cl_create_buffer_blur(t_cl *cl, t_scene *scene)
{
	cl_int		ret;

	ret = 0;
	if ((cl->memobjs[0] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * WIDTH * HEIGHT, NULL, &ret)) && ret != 0)
		ft_error("clCreateBuffer");
	if ((cl->memobjs[1] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * WIDTH * HEIGHT, NULL, &ret)) && ret != 0)
		ft_error("clCreateBuffer");
}

void			create_cl_blur(t_cl *cl, t_scene *scene)
{
	cl_int		ret;
	size_t		log_size;

	if ((cl->kernel = clCreateKernel(cl->program, "blur_x", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	else
		cl_create_buffer_blur(cl, scene);
	if ((cl->kernel = clCreateKernel(cl->program, "blur_y", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	else
		cl_create_buffer_blur(cl, scene);
}
