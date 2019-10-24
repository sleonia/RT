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
*/

t_light		*init_light(t_light *light)
{
	t_light		*tmp;
	t_pos		*center2;
	t_pos		*center3;

	light = (t_light *)ft_memalloc(sizeof(t_light));
	light->type = 'A';
	light->intensity = 0.2;
//
	light->next = (t_light *)ft_memalloc(sizeof(t_light));
	center2 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = light->next;
	tmp->position = insert(2, 1, 0, center2);
	tmp->type = 'P';
	tmp->intensity = 0.6;
//
	tmp->next = (t_light *)ft_memalloc(sizeof(t_light));
	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->type = 'D';
	tmp->intensity = 0.2;
	tmp->position = insert(1, 4, 4, center3);
	return (light);
}

double		computer_lighting(t_pos *p, t_pos *n, t_light *light)
{
	double		intens;
	t_light		*tmp;
	t_pos		l;
	double		n_dot_1;

	intens = 0.0;
	tmp = light;
	while (tmp)
	{
		if (tmp->type == 'A')
			intens += tmp->intensity;
		else
		{
			if (tmp->type == 'P')
				l = vector_minus(tmp->position, p);
			else if (tmp->type == 'D')
			{
				l.x = tmp->position->x;
				l.y = tmp->position->y;
				l.z = tmp->position->z;
			}
			n_dot_1 = dot(n, &l);
			if (n_dot_1 > 1)
				intens += tmp->intensity * n_dot_1 / (vector_len(n) * vector_len(&l));
		}
		tmp = tmp->next;
	}
	return (intens);
}