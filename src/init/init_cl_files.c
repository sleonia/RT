/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:55:40 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 20:56:07 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char				**init_cl_files(void)
{
	char			**files;

	files = (char **)ft_memalloc(sizeof(char *) * 4);
	files[0] = "./src_opencl/intersection.cl";
	files[1] = "./src_opencl/uv_mapping.cl";
	files[2] = "./src_opencl/ray_trace.cl";
	files[3] = NULL;
	return (files);
}
