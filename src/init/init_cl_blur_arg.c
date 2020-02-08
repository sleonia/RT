/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_blur_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:15:57 by deladia           #+#    #+#             */
/*   Updated: 2020/02/08 05:02:05 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_arg_blur(t_cl *cl, t_sdl *sdl)
{
	int		ret;
	int		*output;

	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[0], CL_TRUE, 0,
								sizeof(cl_int) * HEIGHT * WIDTH,
								(cl_int *)sdl->screen[0]->sur->pixels, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueWriteBuffer(cl->cmd_queue, cl->memobjs[6], CL_TRUE, 0,
								sizeof(cl_int) * HEIGHT * WIDTH,
								(cl_int *)sdl->screen[0]->sur->pixels, 0, NULL,
								NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueNDRangeKernel(cl->cmd_queue, cl->kernel, 2, NULL,
			cl->global_work_size, cl->local_work_size, 0, NULL, NULL)) != 0)
		func_error(-10);
	if ((ret = clEnqueueReadBuffer(cl->cmd_queue, cl->memobjs[6], CL_TRUE, 0,
									HEIGHT * WIDTH * sizeof(cl_int),
									(cl_int *)sdl->screen[0]->sur->pixels, 0, NULL,
									NULL)) != 0)
		func_error(-12);
}

int				set_opencl_arg_for_blur(t_cl *cl, t_sdl *sdl)
{
	cl_int		ret;

	ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->memobjs[0]);
	ret |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->memobjs[6]);
	if (ret != 0)
		func_error(-9);
	set_arg_blur(cl, sdl);
	return (0);
}
