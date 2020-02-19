/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_get_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:11:18 by ccriston          #+#    #+#             */
/*   Updated: 2020/02/19 21:11:22 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		intersect_ray_plane(cl_float3 o, cl_float3 d, t_plane *pl,
														float *dist_i)
{
	float		a;

	cl_normalize(&pl->axis);
	cl_normalize(&d);
	a = dot(d, pl->axis);
	if (fabs(a) < 0.000001f)
		return (0);
	*dist_i = (pl->dist - dot(o, pl->axis)) / a;
	if ((*dist_i) < 0.02f)
		return (0);
	return (1);
}

static int		intersect_ray_cone(cl_float3 o, cl_float3 d,
									t_cone *c, float *dist_i)
{
	cl_float3	s;
	cl_float3	q;
	cl_float3	abc;
	cl_float2	t12;

	s = cl_minus(d, cl_mult_n(c->axis, dot(d, c->axis)));
	q = cl_minus(o, cl_sum(c->center, cl_mult_n(c->axis,
			dot((cl_minus(o, c->center)), c->axis))));
	abc.x = cos(c->tan) * cos(c->tan) * dot(s, s) - sin(c->tan)
			* sin(c->tan) * dot(d, c->axis) * dot(d, c->axis);
	abc.y = 2 * cos(c->tan) * cos(c->tan) * dot(s, q) - 2 * sin(c->tan)
	* sin(c->tan) * dot(d, c->axis) * dot(cl_minus(o, c->center), c->axis);
	abc.z = cos(c->tan) * cos(c->tan) * dot(q, q) - sin(c->tan)
		* sin(c->tan) * dot(cl_minus(o, c->center), c->axis)
		* dot(cl_minus(o, c->center), c->axis);
	if (abc.y * abc.y - 4 * abc.x * abc.z < 0.f)
		return (0);
	t12.x = (-abc.y + sqrt(abc.y * abc.y - 4 * abc.x * abc.z)) / (2.f * abc.x);
	t12.y = (-abc.y - sqrt(abc.y * abc.y - 4 * abc.x * abc.z)) / (2.f * abc.x);
	*dist_i = (float)minn(t12.x, t12.y);
	if ((dot(c->axis, (cl_sum(cl_mult_n(d, *dist_i), cl_minus(o, c->center))))
		* dot(c->axis, (cl_sum(cl_mult_n(d, *dist_i), cl_minus(o, c->center)))))
		<= (c->length / 2) * (c->length / 2) && *dist_i > 0.002f)
		return (1);
	return (0);
}

int				type_plane(cl_float3 o, cl_float3 d,
								t_object *object, cl_float2 *dist)
{
	int			t12;

	dist->y = 0.f;
	t12 = intersect_ray_plane(o, d, &(object)->object.plane, &dist->y);
	if (t12 && dist->y < dist->x)
	{
		dist->x = dist->y;
		return (1);
	}
	return (0);
}

int				type_cone(cl_float3 o, cl_float3 d,
								t_object *object, cl_float2 *dist)
{
	int			t12;

	dist->y = 0.f;
	t12 = intersect_ray_cone(o, d, &(object)->object.cone, &dist->y);
	if (t12 && dist->y < dist->x)
	{
		dist->x = dist->y;
		return (1);
	}
	return (0);
}
