/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:38:23 by deladia           #+#    #+#             */
/*   Updated: 2020/02/07 14:39:50 by deladia          ###   ########.fr       */
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
									t_cylinder *cyl, float *dist_i)
{
	cl_float3	s;
	cl_float3	q;
	float		b;
	float		c;
	float		discriminate;

	s = cl_minus(d, cl_mult_n(cyl->axis, dot(d, cyl->axis)));
	q = cl_minus(o, cyl->center);
	q = cl_minus(q, cl_mult_n(cyl->axis, dot(q, cyl->axis)));
	b = 2 * dot(s, q);
	c = dot(q, q) - cyl->radius * cyl->radius;
	discriminate = b * b - 4 * dot(s, s) * c;
	if (fabs(discriminate) < 0.000001f)
		return (0);
	if (discriminate < 0.f)
		return (0);
	*dist_i = (-b - sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0.002f)
		return (1);
	*dist_i = (-b + sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0.002f)
		return (2);
	return (0);
}

static int		intersect_ray_plane(cl_float3 o, cl_float3 d, t_plane *pl,
														float *dist_i)
{
	float	a;

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
									t_cone *cone, float *dist_i)
{
	cl_float3	s;
	cl_float3	q;
	cl_float3	abc;
	float		discriminate;
	cl_float2	t12;

	s = cl_minus(d, cl_mult_n(cone->axis, dot(d, cone->axis)));
	q = cl_minus(o, cl_minus(cone->center, cl_mult_n(cone->axis,
			dot((cl_minus(o, cone->center)), cone->axis))));
	abc.x = cos(cone->tan) * cos(cone->tan) * dot(s, s) - sin(cone->tan)
			* sin(cone->tan) * dot(d, cone->axis) * dot(d, cone->axis);
	abc.y = 2 * cos(cone->tan) * cos(cone->tan) * dot(s, q) - 2 * sin(cone->tan)
		* sin(cone->tan) * dot(d, cone->axis) * dot(cl_minus(o, cone->center),
		cone->axis);
	abc.z = cos(cone->tan) * cos(cone->tan) * dot(q, q) - sin(cone->tan)
		* sin(cone->tan) * dot(cl_minus(o, cone->center), cone->axis)
		* dot(cl_minus(o, cone->center), cone->axis);
	discriminate = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminate < 0.f)
		return (0);
	t12.x = (-abc.y + sqrt(discriminate)) / (2.f * abc.x);
	t12.y = (-abc.y - sqrt(discriminate)) / (2.f * abc.x);
	*dist_i = MIN(t12.x, t12.y);
	if (*dist_i > 0.002f)
	{
		if (acos(fabs(dot(d, cone->axis))) > cone->tan)
			return (1);
		return (2);
	}
	*dist_i = MAX(t12.x, t12.y);
	if (*dist_i > 0.002f)
	{
		if (acos(fabs(dot(d, cone->axis))) > cone->tan)
			return (2);
		return (1);
	}
	return (0);
}

t_object		*get_object(t_scene *scene, int x, int y)
{
	cl_float3	d;
	t_object	*closest;
	cl_float2	dist;
	int			i;
	int			t12;

	d = cl_minus(cl_mult_n(scene->cam.ox, ((float)x * 1.f / WIDTH) - 0.5f),
		cl_mult_n(scene->cam.oy, ((float)y * 1.f / WIDTH) - 0.5f));
	d = cl_minus(d, scene->cam.oz);
	cl_normalize(&d);
	dist.x = MAX_DIST + 1.f;
	i = 0;
	while (i < scene->count_objects)
	{
		if (scene->object[i].type == o_sphere)
		{
			dist.y = 0.f;
			t12 = intersect_ray_sphere(scene->cam.pos, d,
				&(scene->object + i)->object.sphere, &dist.y);
			if (t12 && dist.y < dist.x)
			{
				dist.x = dist.y;
				closest = &(scene->object[i]);
			}
		}
		else if (scene->object[i].type == o_plane)
		{
			dist.y = 0.f;
			t12 = intersect_ray_plane(scene->cam.pos, d,
				&(scene->object + i)->object.plane, &dist.y);
			if (t12 && dist.y < dist.x)
			{
				dist.x = dist.y;
				closest = &(scene->object[i]);
			}
		}
		else if (scene->object[i].type == o_cone)
		{
			dist.y = 0.f;
			t12 = intersect_ray_cone(scene->cam.pos, d,
				&(scene->object + i)->object.cone, &dist.y);
			if (t12 && dist.y < dist.x)
			{
				dist.x = dist.y;
				closest = &(scene->object[i]);
			}
		}
		else if (scene->object[i].type == o_cylinder)
		{
			dist.y = 0.f;
			t12 = intersect_ray_cylinder(scene->cam.pos, d,
				&(scene->object + i)->object.cylinder, &dist.y);
			if (t12 && dist.y < dist.x)
			{
				dist.x = dist.y;
				closest = &(scene->object[i]);
			}
		}
		i++;
	}
	if (dist.x < MAX_DIST)
		return (closest);
	return (NULL);
}
