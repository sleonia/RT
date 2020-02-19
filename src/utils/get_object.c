/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:38:23 by deladia           #+#    #+#             */
/*   Updated: 2020/02/19 22:27:48 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object		*check(t_scene *s, cl_float2 dist, cl_float3 d, int i)
{
	t_object	*closest;

	while (++i < s->count_objects)
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
	}
	return ((dist.x < MAX_DIST) ? closest : NULL);
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
	i = -1;
	return (check(s, dist, d, i));
}
