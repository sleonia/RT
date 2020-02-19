/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:38:23 by deladia           #+#    #+#             */
/*   Updated: 2020/02/19 20:46:30 by ccriston         ###   ########.fr       */
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
		q = (cl_float2){{cl_length(cl_minus(p, n1)) - tor->bigr, cl_length(n1)}};
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

t_object		*get_object(t_scene *s, int x, int y)
{
	cl_float3	d;
	t_object	*closest;
	cl_float2	dist;
	int			i;

	d = cl_minus(cl_mult_n(s->cam.ox, ((float)x * 1.f / WIDTH) - 0.5f),
		cl_mult_n(s->cam.oy, ((float)y * 1.f / WIDTH) - 0.5f));
	d = cl_minus(d, s->cam.oz);
	cl_normalize(&d);
	dist.x = MAX_DIST + 1.f;
	i = 0;
	while (i < s->count_objects)
	{
		if (s->object[i].type == o_sphere && type_sphere(s->cam.pos, d,
			(s->object + i), &dist))
			closest = &s->object[i];
		else if (s->object[i].type == o_plane && type_plane(s->cam.pos, d,
			(s->object + i), &dist))
			closest = &s->object[i];
		else if (s->object[i].type == o_cone && type_cone(s->cam.pos, d,
			(s->object + i), &dist))
			closest = &s->object[i];
		else if (s->object[i].type == o_cylinder && type_cylinder(s->cam.pos, d,
			(s->object + i), &dist))
			closest = &s->object[i];
		else if (s->object[i].type == o_parab && type_parab(s->cam.pos, d,
			(s->object + i), &dist))
			closest = &s->object[i];
		else if (s->object[i].type == o_torus && type_torus(s->cam.pos, d,
			(s->object + i), &dist))
			closest = &s->object[i];
		i++;
	}
	if (dist.x < MAX_DIST)
		return (closest);
	return (NULL);
}
