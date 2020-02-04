/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_vectors_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:29:16 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 15:47:14 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	cl_sum(cl_float3 v1, cl_float3 v2)
{
	cl_float3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

cl_float3	cl_minus(cl_float3 v1, cl_float3 v2)
{
	cl_float3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

float		cl_length(cl_float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
