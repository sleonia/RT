/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:25:17 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 14:25:18 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Умножение вектора на число векторов
*/

t_pos		vector_on_number(t_pos *o, double nbr)
{
	t_pos	oc;

	oc.x = o->x * nbr;
	oc.y = o->y * nbr;
	oc.z = o->z * nbr;
	return (oc);
}

/*
** Деление вектора на число векторов
*/

t_pos		vector_div(t_pos *o, double nbr)
{
	t_pos	oc;

	oc.x = o->x / nbr;
	oc.y = o->y / nbr;
	oc.z = o->z / nbr;
	return (oc);
}

/*
** Длина вектора
*/

double		vector_len(t_pos *o)
{
	return (sqrt(o->x * o->x + o->y * o->y + o->z * o->z));
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
** Сумма векторов
*/

t_pos		vector_pus(t_pos *o, t_pos *center)
{
	t_pos	oc;

	oc.x = o->x + center->x;
	oc.y = o->y + center->y;
	oc.z = o->z + center->z;
	return (oc);
}
