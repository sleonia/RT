/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 04:07:05 by thorker           #+#    #+#             */
/*   Updated: 2020/02/01 15:22:34 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		spherical_coor(float phi, float tetta)
{
	cl_float3	vec;

	vec.s[0] = sinf(tetta) * cosf(phi);
	vec.s[2] = sinf(tetta) * sinf(phi);
	vec.s[1] = cosf(tetta);
	return (vec);
}

cl_float3		spher_norm(cl_float3 vec)
{
	cl_float3	normal;

	if ((fabsf(vec.s[1]) < 0.00001f))
	{
		normal.s[0] = 0.f;
		normal.s[1] = -1.f;
		normal.s[2] = 0.f;
	}
	else
	{
		normal.s[0] = vec.s[0];
		normal.s[1] = -(vec.s[0] * vec.s[0] + vec.s[2] * vec.s[2]) / vec.s[1];
		normal.s[2] = vec.s[2];
	}
	return (normal);
}

void			calc_screen(t_cam *cam)
{
	cl_float3	dec_coor;
	cl_float3	ox;
	cl_float3	oy;
	cl_float3	oz;

	if ((*cam).tetta == 0.0f)
		(*cam).tetta = 0.0001;
	dec_coor = spherical_coor((*cam).phi, (*cam).tetta);
	dec_coor = cl_sum(dec_coor, (*cam).pos);
	oz = cl_minus((*cam).pos, dec_coor);
	oy = spher_norm(oz);
	if ((*cam).tetta > (float)M_PI_2 - 0.00001f)
		oy = cl_mult_n(oy, (-1));
	ox = cl_cross(oz, oy);
	cl_normalize(&ox);
	cl_normalize(&oy);
	(*cam).ox = ox;
	(*cam).oy = oy;
	(*cam).oz = oz;
}
