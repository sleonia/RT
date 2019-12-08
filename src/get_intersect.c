/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 21:28:06 by deladia           #+#    #+#             */
/*   Updated: 2019/12/08 19:55:10 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** 		Решает квадратное уравнение и возвращает два корня если есть, если нет то INF
*/

// t_result	intersect_ray_sphere(t_pos *o, t_pos *d, t_sphere *sphere)
// {
// 	t_pos		oc;
// 	double		k1;
// 	double		k2;
// 	double		k3;
// 	t_result	res;


// 	oc = vector_minus(o, &sphere->center);
// 	k1 = ft_dot(d, d);
// 	k2 = 2 * ft_dot(&oc, d);
// 	k3 = ft_dot(&oc, &oc) - sphere->radius * sphere->radius;
// 	if (k2 * k2 - 4 * k1 * k3 < 0)
// 	{
// 		res.t1 = INFINITY;
// 		res.t2 = INFINITY;
// 		return (res);
// 	}
// 	res.t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
// 	res.t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
// 	return (res);
// }

// t_result    intersect_ray_cylinder(t_pos *o, t_pos *d, t_cylinder *cyl)
// {
// 	t_result    res;
// 	t_pos oc;
// 	double  a;
// 	double  b;
// 	double  c;
// 	double  discr;

// 	oc = vector_minus(o, &cyl->center);
// 	a = ft_dot(d,d) - ft_dot(d,&cyl->axis) * ft_dot(d,&cyl->axis);
// 	c = ft_dot(&oc,&oc) - ft_dot(&oc,&cyl->axis) * ft_dot(&oc,&cyl->axis) - cyl->radius * cyl->radius;
// 	b = ft_dot(d,&oc) - ft_dot(d,&cyl->axis) * ft_dot(&oc,&cyl->axis);
// 	discr = b*b - a*c;
// 	if (discr < 0.0 )
// 	{
// 		res.t1 = INFINITY;
// 		res.t2 = INFINITY;
// 	}
// 	else
// 	{
// 		res.t1 = (-b - sqrt(discr))/(a);
// 		res.t2 = (-b + sqrt(discr))/(a);
// 	}
// 	return (res);
// }

// /*провеяет, лежит ли точка в плоскости*/
// t_result intersect_ray_plane(t_pos *cam, t_pos *view, t_plane *pl) //view - точка экрана
// {
// 	double  t;
// 	t_pos   oc;
// 	t_pos   min;
// 	t_result res;

// 	oc = vector_minus(cam,&pl->center);
// 	min = vector_on_number(&oc,-1);
// 	t = ft_dot(&min,&pl->normal) / ft_dot(view,&pl->normal);
// 	res.t1 = t;
// 	res.t2 = INFINITY;
// 	return (res);
// }

// t_result    intersect_ray_cone(t_pos *o, t_pos *d, t_cone *cone)
// {
// 	t_result    res;
// 	t_pos oc;
// 	double  a;
// 	double  b;
// 	double  c;
// 	double  discr;

// 	oc = vector_minus(o, &cone->center);
// 	a = ft_dot(d,d) - (1 + cone->tan * cone->tan)*ft_dot(d,&cone->axis) * ft_dot(d,&cone->axis);
// 	c = ft_dot(&oc,&oc) - (1 + cone->tan * cone->tan)*ft_dot(&oc,&cone->axis) * ft_dot(&oc,&cone->axis);
// 	b = ft_dot(d,&oc) - (1 + cone->tan * cone->tan)*ft_dot(d,&cone->axis) * ft_dot(&oc,&cone->axis);
// 	discr = b*b - a*c;
// 	if (discr < 0.0 )
// 	{
// 		res.t1 = INFINITY;
// 		res.t2 = INFINITY;
// 	}
// 	else
// 	{
// 		res.t1 = (-b - sqrt(discr))/(a);
// 		res.t2 = (-b + sqrt(discr))/(a);
// 	}
// 	return (res);
// }

// /*
// ** 		Находит ближайшую точку в позиции (x, y) среди всех сфер и возвращает укзатель на сферу и ближайшую точку пересечения
// */

// t_result	get_intersect(t_pos *o, t_pos *d, t_object *obj)
// {
// 	if (obj->type == o_sphere)
// 		return (intersect_ray_sphere(o, d, &obj->objects->sphere));
// 	else if (obj->type == o_plane)
// 		return (intersect_ray_plane(o, d, &obj->objects->plane));
// 	else if (obj->type == o_cone)
// 		return (intersect_ray_cone(o, d, &obj->objects->cone));
// 	else
// 		return (intersect_ray_cylinder(o, d, &obj->objects->cylinder));
// }