/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2019/12/07 22:17:13 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** 		Костыльное добавление источников света
** 		НУЖЕН ПАРСЕР!!!
**		Разобраться с источниками света
*/

t_light		**init_light(void)
{
	t_light **light;

	//ambient - окружающий свет
	light = (t_light **)ft_memalloc(sizeof(t_light *) * 3);
	light[0] = (t_light *)ft_memalloc(sizeof(t_light));
	light[0]->type = 'A';
	light[0]->intensity = 0.2;

	//point - точечный источник света
	light[1] = (t_light *)ft_memalloc(sizeof(t_light));
	light[1]->position = (t_pos){3, 1, -1};
	light[1]->type = 'P';
	light[1]->intensity = 0.6;
//
//	tmp->next = (t_light *)ft_memalloc(sizeof(t_light));
//	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
//	tmp = tmp->next;
//	tmp->position = insert(3, 1, -2, center3);
//	tmp->type = 'P';
//	tmp->intensity = 0.6;
//	directional - направленный источник света
	light[2] = (t_light *)ft_memalloc(sizeof(t_light));
	light[2]->type = 'D';
	light[2]->intensity = 0.2;
	light[2]->position = (t_pos){1, 4, 4};
	return (light);
}

/*
**  	Вычисляет яркость пикселя сферы в зависимости от источников света
*/

double		computer_lighting(t_pos *p, t_pos *n, t_pos *v, int specular, t_scene *scene)
{
	double		intens;
	t_light		**tmp;
	t_pos		l;
	double		n_dot_l;
	double		r_dot_v;
	t_pos		r;
	t_pos		buf;
	t_return	shadow;
	double		t_max;
	int 		i;

	i = 0;
	intens = 0.0;
	tmp = scene->light;
	//костыль чтобы занулить l
	l = vector_on_number(&l, 0);
	while (i < 3)
	{
		if (tmp[i]->type == 'A' && !scene->off->ambient)
			intens += tmp[i]->intensity;
		else
		{
			if (tmp[i]->type == 'P' && !scene->off->point)
			{
				l = vector_minus(&tmp[i]->position, p);
				t_max = 1.0;
			}
			else if (tmp[i]->type == 'D' && !scene->off->directional)
			{
				l.x = tmp[i]->position.x;
				l.y = tmp[i]->position.y;
				l.z = tmp[i]->position.z;
				t_max = INFINITY;
			}
			// Проверка тени
			if (t_max)
			{
				shadow = closest_intersection(p, &l, 0.001, t_max, scene->object);
				if (shadow.closest_object != NULL)
				{
					i++;
					continue ;
				}
				// Диффузность
				n_dot_l = ft_dot(n, &l);
				if (n_dot_l > 0)
					intens += tmp[i]->intensity * n_dot_l / (vector_len(n) * vector_len(&l));
				// Зеркальность
				if (specular != -1)
				{
					buf = vector_on_number(n, 2);
					buf = vector_on_number(&buf, ft_dot(n, &l));
					r = vector_minus(&buf, &l);
					r_dot_v = ft_dot(&r, v);
					if (r_dot_v > 0)
						intens += tmp[i]->intensity * pow(r_dot_v / (vector_len(&r) * vector_len(v)), specular);
				}
			}
		}
		i++;
	}
	if (intens > 1.0)
		return (1.0);
	return (intens);
}
