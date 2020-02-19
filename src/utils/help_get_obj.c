/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_get_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:11:09 by ccriston          #+#    #+#             */
/*   Updated: 2020/02/19 21:11:12 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		intersect_ray_sphere(cl_float3 o, cl_float3 d,
								t_sphere *sphere, float *dist_i)
{
	cl_float3	oc;
	float		k1;
	float		k2;
	float		k3;

	oc = cl_minus(o, sphere->center);
	k1 = dot(d, d);
	k2 = 2 * dot(oc, d);
	k3 = dot(oc, oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
		return (0);
	*dist_i = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.002f)
		return (1);
	*dist_i = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.002f)
		return (2);
	return (0);
}

static int		intersect_ray_cylinder(cl_float3 o, cl_float3 d,
									t_cylinder *c, float *dist_i)
{
	cl_float3	s;
	cl_float3	q;
	float		b;
	float		e;
	float		discriminate;

	s = cl_minus(d, cl_mult_n(c->axis, dot(d, c->axis)));
	q = cl_minus(o, c->center);
	q = cl_minus(q, cl_mult_n(c->axis, dot(q, c->axis)));
	b = 2 * dot(s, q);
	e = dot(q, q) - c->radius * c->radius;
	if ((discriminate = b * b - 4 * dot(s, s) * e) < 0.f)
		return (0);
	*dist_i = (-b - sqrt(discriminate)) / (2 * dot(s, s));
	if ((dot(c->axis, (cl_sum(cl_mult_n(d, *dist_i), q))) * dot(c->axis,
		(cl_sum(cl_mult_n(d, *dist_i), q))))
		<= (c->length / 2) * (c->length / 2) && *dist_i > 0.002f)
		return (1);
	*dist_i = (-b + sqrt(discriminate)) / (2 * dot(s, s));
	if ((dot(c->axis, (cl_sum(cl_mult_n(d, *dist_i), q))) * dot(c->axis,
		(cl_sum(cl_mult_n(d, *dist_i), q))))
		<= (c->length / 2) * (c->length / 2) && *dist_i > 0.002f)
		return (2);
	return (0);
}

int				type_sphere(cl_float3 o, cl_float3 d,
								t_object *object, cl_float2 *dist)
{
	int			t12;

	dist->y = 0.f;
	t12 = intersect_ray_sphere(o, d, &(object)->object.sphere, &dist->y);
	if (t12 && dist->y < dist->x)
	{
		dist->x = dist->y;
		return (1);
	}
	return (0);
}

int				type_cylinder(cl_float3 o, cl_float3 d,
									t_object *object, cl_float2 *dist)
{
	int			t12;

	dist->y = 0.f;
	t12 = intersect_ray_cylinder(o, d, &(object)->object.cylinder, &dist->y);
	if (t12 && dist->y < dist->x)
	{
		dist->x = dist->y;
		return (1);
	}
	return (0);
}
