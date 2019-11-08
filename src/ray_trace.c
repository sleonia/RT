/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putin_clone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalmer <hfalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:28:06 by hfalmer           #+#    #+#             */
/*   Updated: 2019/10/24 23:10:47 by hfalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			color_scale(int color, double c)
{
	int	red;
	int	green;
	int	blue;

	red = (color & 0xFF0000) >> 16;
	red = (int)((double)red * c);
	green = (color & 0x00FF00) >> 8;
	green = (int)((double)green * c);
	blue = (color & 0x0000FF);
	blue = (int)((double)blue * c);
	return ((red << 16) | (green << 8) | blue);
}

t_return	closest_intersection(t_pos *o, t_pos *d, t_min_max mn,
		t_object *obj)
{
	t_result	res;
	t_object	*tmp_obj;
	t_return	ret;

	ret.closest_t = INFINITY;
	ret.closest_obj = NULL;
	tmp_obj = obj;
	while (tmp_obj)
	{
		res = get_intersect(o, d, tmp_obj);
		if (res.t1 >= mn.min && res.t1 <= mn.max && res.t1 < ret.closest_t)
		{
			ret.closest_t = res.t1;
			ret.closest_obj = tmp_obj;
		}
		if (res.t2 >= mn.min && res.t2 <= mn.max && res.t2 < ret.closest_t)
		{
			ret.closest_t = res.t2;
			ret.closest_obj = tmp_obj;
		}
		tmp_obj = tmp_obj->next;
	}
	return (ret);
}

t_pos		reflect_ray(t_pos *r, t_pos *n)
{
	t_pos	ret;
	t_pos	a;
	t_pos	b;

	a = vector_on_number(n, 2);
	b = vector_on_number(&a, dot(r, n));
	ret = vector_minus(&b, r);
	return (ret);
}

int			trace_ray(t_pos *o, t_pos *d, t_min_max mn, t_scene *scene)
{
	t_pos			p;
	t_pos			n;
	t_pos			buf;
	t_pos			r;
	t_for_ray_trace	a;

	a.ret = closest_intersection(o, d, mn, scene->object);
	if (a.ret.closest_obj == NULL)
		return (BLACK);
	buf = vector_on_number(d, a.ret.closest_t);
	p = vector_pus(o, &buf);
	n = get_obj_normal(&p, &a.ret, o, d);
	buf = vector_on_number(d, -1);
	scene->specular = a.ret.closest_obj->specular;
	a.local_color = color_scale(a.ret.closest_obj->color,
		computer_lighting(&p, &n, &buf, scene));
	if (scene->depth <= 0 || a.ret.closest_obj->reflective <= 0 ||
			scene->off->reflect)
		return (a.local_color);
	r = reflect_ray(&buf, &n);
	scene->depth--;
	a.reflected_color = trace_ray(&p, &r, (t_min_max){0.001, INFINITY}, scene);
	return (color_scale(a.local_color, 1 - a.ret.closest_obj->reflective)
			+ color_scale(a.reflected_color, a.ret.closest_obj->reflective));
}
