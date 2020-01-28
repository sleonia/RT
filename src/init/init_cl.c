/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:19:02 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 10:19:24 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			**init_files_cl(void)
{
	char		**files;

	files = (char **)ft_memalloc(sizeof(char *) * 4);
	files[0] = "./src_opencl/intersection.cl";
	files[1] = "./src_opencl/uv_mapping.cl";
	files[2] = "./src_opencl/ray_trace.cl";
	files[3] = NULL;
	return (files);
}
