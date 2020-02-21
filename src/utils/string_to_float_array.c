/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_float_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:00:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 13:36:30 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		*string_to_float_array(char *str)
{
	cl_float3	value;
	cl_float3	*ptr;
	char		**split;

	if (!(split = ft_strsplit(str, ' ')))
		ft_error(ERROR_MALLOC);
	if (ft_len_arr((void **)(split)) >= 3)
	{
		value.s[0] = atof(split[0]);
		value.s[1] = atof(split[1]);
		value.s[2] = atof(split[2]);
	}
	else
	{
		value.s[0] = 0.f;
		value.s[1] = 0.f;
		value.s[2] = 0.f;	
	}
	ft_destroy_string_arr(split);
	ptr = &value;
	return (ptr);
}
