/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:55:40 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 15:22:34 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cl			*init_cl(t_key_value *json, t_rt *rt)
{
	t_cl		*opencl;

	if ((opencl = (t_cl *)ft_memalloc(sizeof(t_cl))) == NULL)
		ft_error(ERROR_INPUT);
	opencl->files = init_cl_files();
	read_kernel(opencl, opencl->files);
	create_cl(opencl, rt->sdl, rt->scene);
	return (opencl);
}

char			**init_cl_files(void)
{
	char			**files;

	files = (char **)ft_memalloc(sizeof(char *) * 4);
	files[0] = "./src_opencl/intersection.cl";
	files[1] = "./src_opencl/uv_mapping.cl";
	files[2] = "./src_opencl/ray_trace.cl";
	files[3] = NULL;
	return (files);
}
