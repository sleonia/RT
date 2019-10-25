/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2019/10/24 13:05:16 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** 		Костыльное добавление источников света
** 		НУЖЕН ПАРСЕР!!!
**		Разобраться с источниками света
*/

t_light		*init_light(t_light *light)
{
	t_light		*tmp;
	t_pos		*center2;
	t_pos		*center3;
	t_pos		*center4;

	//ambient - окружающий свет
	light = (t_light *)ft_memalloc(sizeof(t_light));
	light->type = 'A';
	light->intensity = 0.2;

	//point - точечный источник света
	light->next = (t_light *)ft_memalloc(sizeof(t_light));
	center2 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = light->next;
	tmp->position = insert(3, 1, 0, center2);
	tmp->type = 'P';
	tmp->intensity = 0.6;
//
//	tmp->next = (t_light *)ft_memalloc(sizeof(t_light));
//	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
//	tmp = tmp->next;
//	tmp->position = insert(-3, 1, 0, center3);
//	tmp->type = 'P';
//	tmp->intensity = 0.6;
//	directional - направленный источник света
	tmp->next = (t_light *)ft_memalloc(sizeof(t_light));
	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->type = 'D';
	tmp->intensity = 0.2;
	tmp->position = insert(1, 4, 4, center3);

//	tmp->next = (t_light *)ft_memalloc(sizeof(t_light));
//	center4 = (t_pos *)ft_memalloc(sizeof(t_pos));
//	tmp = tmp->next;
//	tmp->type = 'P';
//	tmp->intensity = 0.4;
//	tmp->position = insert(-100, -100, -100, center4);
	return (light);
}

/*
**  	Вычисляет яркость пикселя сферы в зависимости от источников света
*/

double		computer_lighting(t_pos *p, t_pos *n, t_pos *v, int s, t_light *light, t_sphere *sphere)
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
	tmp = light;
	while (tmp)
	{
		if (tmp->type == 'A')
			intens += tmp->intensity;
		else
		{
			if (tmp->type == 'P')
			{
				l = vector_minus(tmp->position, p);
				t_max = 1.0;
			}
			else if (tmp->type == 'D')
			{
				l.x = tmp->position->x;
				l.y = tmp->position->y;
				l.z = tmp->position->z;
				t_max = INFINITY;
			}
			// Проверка тени
			shadow = closest_intersection(p, &l, 0.001, t_max, sphere);
			if (shadow.closest_sphere != NULL)
			{
				tmp = tmp->next;
				continue;
			}
			// Диффузность
			n_dot_l = dot(n, &l);
			if (n_dot_l > 1)
				intens += tmp->intensity * n_dot_l / (vector_len(n) * vector_len(&l));
			// Зеркальность
			if (s != -1)
			{
				buf = vector_on_number(n, 2);
				buf = vector_on_number(&buf, dot(n, &l));
				r =  vector_minus(&buf, &l);
				r_dot_v = dot(&r, v);
				if (r_dot_v > 0)
					intens += tmp->intensity * pow(r_dot_v / (vector_len(&r) * vector_len(v)), s);
			}
		}
		tmp = tmp->next;
	}
//	printf("%f\n", intens);
	if (intens >= 1.0)
		return (1.0);
	return (intens);
}