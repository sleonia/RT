/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:59:13 by deladia           #+#    #+#             */
/*   Updated: 2019/10/24 10:59:16 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Инициализация вектора
*/

t_pos		*insert(int x, int y, int z, t_pos *pos)
{
	pos->x = x;
	pos->y = y;
	pos->z = z;
	return (pos);
}

/*
** Преобразование координат в координаты холста
*/

t_pos		*canvas_to_viewport(int x, int y, t_pos *pos)
{
	pos->x = (double)x * VW / WIDTH;
	pos->y = (double)y * VH / HEIGHT;
	pos->z = D;
	return (pos);
}

/*
** Разность векторов
*/

t_pos		vector_minus(t_pos *o, t_pos *center)
{
	t_pos	oc;

	oc.x = o->x - center->x;
	oc.y = o->y - center->y;
	oc.z = o->z - center->z;
	return (oc);
}

/*
** Скалярное произведение векторов
*/

double		dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
