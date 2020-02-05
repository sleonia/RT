/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_blur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:15:57 by deladia           #+#    #+#             */
/*   Updated: 2020/02/05 19:40:57 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	cl_create_buffer_blur_1(cl, scene);
}

void			create_cl_blur(t_cl *cl, t_scene *scene)
{
	cl_int		ret;
	size_t		log_size;

	if ((cl->kernel = clCreateKernel(cl->program, "blur", &ret)) && ret != 0)
		ft_error("clBuildProgram");
	cl_create_buffer_blur(cl, scene);
}
