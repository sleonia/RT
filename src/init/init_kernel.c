/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:37:29 by deladia           #+#    #+#             */
/*   Updated: 2020/02/17 08:14:21 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			create_kernel_rt(t_cl *cl)
{
	cl_int		ret;

	ret = 0;
	ret |= clReleaseKernel(cl->kernel);
	if ((cl->kernel = clCreateKernel(cl->program, "RT", &ret)) && ret != 0)
		ft_error("clBuildProgram");
}

void			create_kernel_blur(t_cl *cl, t_sdl *sdl)
{
	cl_int		ret;

	ret = 0;
	ret |= clReleaseKernel(cl->kernel);
	if ((cl->kernel = clCreateKernel(cl->program, "blur_x", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	set_opencl_arg_for_blur(cl, sdl);
	ret |= clReleaseKernel(cl->kernel);
	if ((cl->kernel = clCreateKernel(cl->program, "blur_y", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	set_opencl_arg_for_blur(cl, sdl);
}
