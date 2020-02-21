/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:46:41 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 04:49:31 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		*string_to_color(char *str)
{
	cl_float3	value;
	cl_float3	*ptr;
	char		**split;

	if (!(split = ft_strsplit(str, ' ')))
		ft_error(ERROR_MALLOC);
	if (ft_len_arr((void **)(split)) >= 3)
	{
		value.s[0] = atof(split[0]) / 255.0;
		value.s[1] = atof(split[1]) / 255.0;
		value.s[2] = atof(split[2]) / 255.0;
	}
	else
		return (NULL);
	ft_destroy_string_arr(split);
	ptr = &value;
	return (ptr);
}
