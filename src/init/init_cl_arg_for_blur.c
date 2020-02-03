/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_arg_for_blur.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 04:22:13 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/03 15:35:57 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_arg_blur_2(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	int		ret;

	if (scene->texture_cnt > 0)
	{
		if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[4], CL_TRUE,
									0, sizeof(cl_int) * scene->texture_length,
									(cl_int *)scene->texture, 0, NULL,
									NULL)) != 0)
			func_error(-10);
		if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[5], CL_TRUE,
									0, sizeof(cl_int) * scene->texture_cnt * 3,
									(cl_int *)scene->texture_param, 0, NULL,
									NULL)) != 0)
			func_error(-10);
	}
	if ((ret = clEnqueueNDRangeKernel(cl->cmd_queue, cl->kernel, 2, NULL,
			cl->global_work_size, cl->local_work_size, 0, NULL, NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueReadBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
									HEIGHT * WIDTH * sizeof(cl_int),
									(cl_int *)sdl->pixels, 0, NULL,
									NULL)) != 0)
		func_error(-12);
}

static void		set_arg_blur_1(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	int		ret;

	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
									sizeof(cl_int) * HEIGHT * WIDTH,
									(cl_int *)sdl->pixels, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[1], CL_TRUE, 0,
								sizeof(t_cam), &scene->cam, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[2], CL_TRUE, 0,
								sizeof(t_object) * scene->count_objects,
								scene->object, 0, NULL, NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[3], CL_TRUE, 0,
									sizeof(t_light) * scene->count_lights,
									scene->light, 0, NULL, NULL)) != 0)
		func_error(-10);
}

int				set_opencl_arg_for_blur(t_cl *cl, t_sdl *sdl, t_scene *scene)
{
	cl_int		ret;

	ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->memobjs[0]);
	ret |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->memobjs[1]);
	ret |= clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->memobjs[2]);
	ret |= clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->memobjs[3]);
	ret |= clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->memobjs[4]);
	ret |= clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->memobjs[5]);
	ret |= clSetKernelArg(cl->kernel, 6, sizeof(cl_int), &scene->count_objects);
	ret |= clSetKernelArg(cl->kernel, 7, sizeof(cl_int), &scene->count_lights);
	ret |= clSetKernelArg(cl->kernel, 8, sizeof(cl_int), &scene->skybox_id);
	ret |= clSetKernelArg(cl->kernel, 9, sizeof(cl_int), &scene->fsaa);
	ret |= clSetKernelArg(cl->kernel, 10, sizeof(cl_int), &scene->ambient);
	if (ret != 0)
		func_error(-9);
	set_arg_blur_1(cl, sdl, scene);
	set_arg_blur_2(cl, sdl, scene);
	return (0);
}
