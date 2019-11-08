/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:42:17 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 17:49:23 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_result	intersect_ray_cone(t_pos *o, t_pos *d, t_cone *cone)
{
	t_pos			x;
	t_discriminant	disc;
	t_result		res;
	double			temp;

	x = vector_minus(o, &cone->center);
	disc.a = dot(d, &cone->axis);
	disc.c = dot(&x, &cone->axis);
	temp = 1 + cone->radius * cone->radius;
	disc.b = 2.0 * (dot(d, &x) - temp * disc.a * disc.c);
	disc.a = dot(d, d) - temp * disc.a * disc.a;
	disc.c = dot(&x, &x) - temp * disc.c * disc.c;
	disc.discriminant = disc.b * disc.b - 4 * disc.a * disc.c;
	temp = 1 / (2 * disc.a);
	if (disc.discriminant < 0.0f)
		return ((t_result){INFINITY, INFINITY});
	disc.discriminant = sqrt(disc.discriminant);
	res.t1 = (-disc.b - disc.discriminant) * temp;
	res.t2 = (-disc.b + disc.discriminant) * temp;
	return (res);
}

t_result	intersect_ray_plane(t_pos *o, t_pos *d, t_plane *plane)
{
	double		a;
	double		b;
	t_pos		c;
	t_result	res;

	b = dot(d, &plane->normal);
	res.t1 = INFINITY;
	res.t2 = INFINITY;
	if (b > 0.0)
		return (res);
	c = vector_minus(o, &plane->center);
	a = dot(&c, &plane->normal);
	res.t1 = -(a / b);
	return (res);
}

t_result	intersect_ray_sphere(t_pos *o, t_pos *d, t_sphere *sphere)
{
	t_pos		oc;
	double		k1;
	double		k2;
	double		k3;
	t_result	res;

	oc = vector_minus(o, &sphere->center);
	k1 = dot(d, d);
	k2 = 2 * dot(&oc, d);
	k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
		return (res);
	}
	res.t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res.t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	return (res);
}

t_result	intersect_ray_cylinder(t_pos *o, t_pos *d, t_cylinder *cylinder)
{
	t_discriminant	disc;
	t_pos			oc;
	t_result		res;

	res.t1 = INFINITY;
	res.t2 = INFINITY;
	oc = vector_minus(o, &cylinder->center);
	disc.a = 1.0 - dot(d, &cylinder->axis) * dot(d, &cylinder->axis);
	disc.b = dot(d, &oc) - dot(d, &cylinder->axis) * dot(&oc, &cylinder->axis);
	disc.c = dot(&oc, &oc) - dot(&oc, &cylinder->axis)
			* dot(&oc, &cylinder->axis) - cylinder->radius * cylinder->radius;
	disc.discriminant = disc.b * disc.b - disc.a * disc.c;
	if (disc.discriminant < 0.0)
		return (res);
	res.t1 = (-disc.b - sqrt(disc.discriminant)) / disc.a;
	return (res);
}

t_result	get_intersect(t_pos *o, t_pos *d, t_object *obj)
{
	if (obj->type == o_sphere)
		return (intersect_ray_sphere(o, d, &obj->objects->sphere));
	else if (obj->type == o_plane)
		return (intersect_ray_plane(o, d, &obj->objects->plane));
	else if (obj->type == o_cone)
		return (intersect_ray_cone(o, d, &obj->objects->cone));
	else
		return (intersect_ray_cylinder(o, d, &obj->objects->cylinder));
}
