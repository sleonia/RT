/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_get_obj3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:11:27 by ccriston          #+#    #+#             */
/*   Updated: 2020/02/19 21:12:22 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		intersect_ray_parab(cl_float3 o, cl_float3 d,
									t_parab *p, float *dist_i)
{
	cl_float3	x;
	float		a;
	float		b;
	float		c;
	float		disc;

	x = cl_minus(o, p->center);
	a = dot(d, d) - dot(d, p->axis) * dot(d, p->axis);
	b = 2.f * dot(d, x) - 2 * dot(d, p->axis) * (dot(x, p->axis) + 2 * p->k);
	c = dot(x, x) - dot(x, p->axis) * (dot(x, p->axis) + 4.f * p->k);
	disc = b * b - 4.f * a * c;
	if (disc < 0.00001f)
		return (0);
	*dist_i = (-b - sqrt(disc)) / (2.f * a);
	if (*dist_i > 0.002f)
		if ((dot(p->axis, (cl_sum(cl_mult_n(d, *dist_i), x))) * dot(p->axis,
		(cl_sum(cl_mult_n(d, *dist_i), x)))) <= (p->length) * (p->length))
			return (1);
	*dist_i = (-b + sqrt(disc)) / (2.f * a);
	if (*dist_i > 0.002f)
		if ((dot(p->axis, (cl_sum(cl_mult_n(d, *dist_i), x))) * dot(p->axis,
		(cl_sum(cl_mult_n(d, *dist_i), x)))) <= (p->length) * (p->length))
			return (2);
	return (0);
}

static int		intersect_ray_torus(cl_float3 o, cl_float3 d,
									t_torus *tor, float *dist_i)
{
	cl_int2		i;
	cl_float2	q;
	cl_float3	current_position;
	cl_float3	p;
	cl_float3	n1;

	i = (cl_int2){{0, 1}};
	while (i.x < 4096)
	{
		current_position = cl_sum(o, cl_mult_n(d, *dist_i));
		p = cl_minus(current_position, tor->center);
		n1 = cl_mult_n(tor->axis, dot(p, tor->axis));
		q = (cl_float2){{cl_length(cl_minus(p, n1)) - tor->bigr,
						cl_length(n1)}};
		if ((i.y == 1) && ((cl_length_v2(q) - tor->r) < -0.00001f))
			i.y = -1;
		*dist_i += fabs(cl_length_v2(q) - tor->r);
		if (*dist_i > MAX_DIST)
			return (0);
		if ((fabs(cl_length_v2(q) - tor->r)) < 0.0001f)
			return (i.y);
		i.x++;
	}
	return (0);
}

int				type_parab(cl_float3 o, cl_float3 d,
									t_object *object, cl_float2 *dist)
{
	int			t12;

	dist->y = 0.f;
	t12 = intersect_ray_parab(o, d, &(object)->object.parab, &dist->y);
	if (t12 && dist->y < dist->x)
	{
		dist->x = dist->y;
		return (1);
	}
	return (0);
}

int				type_torus(cl_float3 o, cl_float3 d,
									t_object *object, cl_float2 *dist)
{
	int			t12;

	dist->y = 0.f;
	t12 = intersect_ray_torus(o, d, &(object)->object.torus, &dist->y);
	if (t12 && dist->y < dist->x)
	{
		dist->x = dist->y;
		return (1);
	}
	return (0);
}
