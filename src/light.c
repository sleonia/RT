/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2019/10/31 16:36:36 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	get_light_dir(t_comp_light *cl, t_light *tmp, t_scene *scene, t_pos *p)
{
	double	t_max;

	t_max = 0.0;
	if (tmp->type == 'P' && !scene->off->point)
	{
		cl->l = vector_minus(&tmp->position, p);
		cl->l = vector_normalize(&cl->l);
		t_max = 1.0;
	}
	else if (tmp->type == 'D' && !scene->off->directional)
	{
		cl->l.x = tmp->position.x;
		cl->l.y = tmp->position.y;
		cl->l.z = tmp->position.z;
		t_max = INFINITY;
	}
	return (t_max);
}

void	get_intens(t_comp_light *cl, t_light *tmp, t_pos *n, t_pos *v)
{
	cl->n_dot_l = dot(n, &cl->l);
	if (cl->n_dot_l > 0)
		cl->intens += tmp->intensity * cl->n_dot_l /
				(vector_len(n) * vector_len(&cl->l));
	if (cl->specular != -1)
	{
		cl->buf = vector_on_number(n, 2);
		cl->buf = vector_on_number(&cl->buf, dot(n, &cl->l));
		cl->r = vector_minus(&cl->buf, &cl->l);
		cl->r_dot_v = dot(&cl->r, v);
		if (cl->r_dot_v > 0)
			cl->intens += tmp->intensity * pow(cl->r_dot_v /
					(vector_len(&cl->r) * vector_len(v)), cl->specular);
	}
}

double	computer_lighting(t_pos *p, t_pos *n, t_pos *v, t_scene *scene)
{
	t_light			*tmp;
	t_return		shadow;
	double			t_max;
	t_comp_light	cl;

	cl.intens = 0.0;
	tmp = scene->light;
	cl.l = vector_on_number(&cl.l, 0);
	cl.specular = scene->specular;
	while (tmp)
	{
		if (tmp->type == 'A' && !scene->off->ambient)
			cl.intens += tmp->intensity;
		else
		{
			t_max = get_light_dir(&cl, tmp, scene, p);
			shadow = closest_intersection(p, &cl.l,
					(t_min_max){0.001, t_max}, scene->object);
			if (shadow.closest_obj == NULL)
				get_intens(&cl, tmp, n, v);
		}
		tmp = tmp->next;
	}
	return (cl.intens > 1.0 ? 1.0 : cl.intens);
}
