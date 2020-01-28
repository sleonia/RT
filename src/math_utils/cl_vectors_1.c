/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_vectors_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:29:13 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 12:30:22 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	cl_mult_n(cl_float3 v1, float n)
{
	cl_float3 v;

	v.x = v1.x * n;
	v.y = v1.y * n;
	v.z = v1.z * n;
	return (v);
}

void		cl_to_norm(cl_float3 *v)
{
	float l;

	l = cl_length(*v);
	v->x = v->x / l;
	v->y = v->y / l;
	v->z = v->z / l;
}

cl_float3	cl_cross(cl_float3 v1, cl_float3 v2)
{
	cl_float3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
