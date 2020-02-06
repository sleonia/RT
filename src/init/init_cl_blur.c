/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_blur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:15:57 by deladia           #+#    #+#             */
/*   Updated: 2020/02/06 22:13:00 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_arg_blur(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	int		ret;
	int		*output;

	// output = (cl_int *)ft_memalloc(sizeof(cl_int) * HEIGHT * WIDTH);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
								sizeof(cl_int) * HEIGHT * WIDTH,
								(cl_int *)sdl->sur->pixels, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[6], CL_TRUE, 0,
								sizeof(cl_int) * HEIGHT * WIDTH,
								(cl_int *)sdl->sur->pixels, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueNDRangeKernel(cl->cmd_queue, cl->kernel, 2, NULL,
			cl->global_work_size, cl->local_work_size, 0, NULL, NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueReadBuffer(cl->cmd_queue, cl->memobjs[6], CL_TRUE, 0,
									HEIGHT * WIDTH * sizeof(cl_int),
									(cl_int *)sdl->sur->pixels, 0, NULL,
									NULL)) != 0)
		func_error(-12);
	// sdl->sur->pixels = (int *)output;
	// free(output);
}

int				set_opencl_arg_for_blur(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	cl_int		ret;

	ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->memobjs[0]);
	ret |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->memobjs[6]);
	if (ret != 0)
		func_error(-9);
	set_arg_blur(cl, sdl, scene);
	return (0);
}

void			create_kernel_blur(t_cl *cl, t_scene *scene)
{
	cl_int		ret;

	// ret |= clFinish(cl->cmd_queue);
	// ret |= clFlush(cl->cmd_queue);
	// ret |= clReleaseCommandQueue(cl->cmd_queue);
	ret |= clReleaseKernel(cl->kernel);
	// ret |= clReleaseMemObject(cl->memobjs[0]);
	// ret |= clReleaseMemObject(cl->memobjs[1]);
	if ((cl->kernel = clCreateKernel(cl->program, "blur_x", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	// ret |= clFinish(cl->cmd_queue);
	// ret |= clFlush(cl->cmd_queue);
	//Что-то тут есть
	// ret |= clReleaseCommandQueue(cl->cmd_queue);
	ret |= clReleaseKernel(cl->kernel);
	// ret |= clReleaseMemObject(cl->memobjs[0]);
	// ret |= clReleaseMemObject(cl->memobjs[1]);
	if ((cl->kernel = clCreateKernel(cl->program, "blur_y", &ret)) && ret != 0)
		ft_error("clBuildProgram");
}
