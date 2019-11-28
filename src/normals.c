/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:35:12 by deladia           #+#    #+#             */
/*   Updated: 2019/11/28 18:51:04 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_pos	get_cone_normal(t_pos *start_ray, t_pos *ray, t_cone *obj,
						 double intersect_dist)
{
	t_pos	ret_normal;
	t_pos	oc;
	double	m;

	oc = vector_minus(start_ray, &obj->center);
	m = dot(ray, &obj->axis) * intersect_dist + dot(&oc, &obj->axis);
	ret_normal = v_minus(v_plus(vector_on_number(ray, intersect_dist), oc),
						 vector_on_number(&obj->axis, (1 + obj->tan * obj->tan) * m));
	return (ret_normal);
}

t_pos	get_cylinder_normal(t_cylinder *obj, t_pos *intersect_point)
{
	t_pos	n;
	t_pos	v;

	v = vector_minus(intersect_point, &obj->center);
	n = vector_on_number(&obj->axis, dot(&v, &obj->axis));
	n = vector_minus(&v, &n);
	return (n);
}

t_pos	get_obj_normal(t_pos *p, t_return *ret, t_pos *o, t_pos *d)
{
	t_pos		n;
	t_object	*obj;

	obj = ret->closest_object;
	if (obj->type == o_sphere)
		n = vector_minus(p, &obj->objects->sphere.center);
	else if (obj->type == o_plane)
		n = obj->objects->plane.normal;
	else if (obj->type == o_cone)
		n = get_cone_normal(o, d, &obj->objects->cone, ret->closest_t);
	else if (obj->type == o_cylinder)
		n = get_cylinder_normal(&obj->objects->cylinder, p);
	n = vector_div(&n, vector_len(&n));
	return (n);
}
