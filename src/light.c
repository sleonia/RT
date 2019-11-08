/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2019/10/31 16:36:36 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** 		Костыльное добавление источников света
** 		НУЖЕН ПАРСЕР!!!
**		Разобраться с источниками света
*/

/*
**  	Вычисляет яркость пикселя сферы в зависимости от источников света
*/

double		computer_lighting(t_pos *p, t_pos *n, t_pos *v, int specular, t_scene *scene)
{
	double		intens;
	t_light		*tmp;
	t_pos		l;
	double		n_dot_l;
	double		r_dot_v;
	t_pos		r;
	t_pos		buf;
	t_return	shadow;
	double		t_max;

	intens = 0.0;
	tmp = scene->light;
	t_max = 0.0;
	//костыль чтобы занулить l
	l = vector_on_number(&l, 0);
	while (tmp)
	{
		if (tmp->type == 'A' && !scene->off->ambient)
			intens += tmp->intensity;
		else
		{
			if (tmp->type == 'P' && !scene->off->point)
			{
				l = vector_minus(&tmp->position, p);
				l = vector_normalize(&l);
				t_max = 1.0;
			}
			else if (tmp->type == 'D' && !scene->off->directional)
			{
				l.x = tmp->position.x;
				l.y = tmp->position.y;
				l.z = tmp->position.z;
				t_max = INFINITY;
			}
			// Проверка тени
			if (t_max)
			{
				shadow = closest_intersection(p, &l, 0.001, t_max, scene->object);
				if (shadow.closest_obj != NULL)
				{
					tmp = tmp->next;
					continue ;
				}
				// Диффузность
				n_dot_l = dot(n, &l);
				if (n_dot_l > 0)
					intens += tmp->intensity * n_dot_l / (vector_len(n) * vector_len(&l));
				// Зеркальность
				if (specular != -1)
				{
					buf = vector_on_number(n, 2);
					buf = vector_on_number(&buf, dot(n, &l));
					r = vector_minus(&buf, &l);
					r_dot_v = dot(&r, v);
					if (r_dot_v > 0)
						intens += tmp->intensity * pow(r_dot_v / (vector_len(&r) * vector_len(v)), specular);
				}
			}
		}
		tmp = tmp->next;
	}
	if (intens > 1.0)
		return (1.0);
	return (intens);
}
