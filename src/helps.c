/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:59:13 by deladia           #+#    #+#             */
/*   Updated: 2020/01/28 00:12:27 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int 		*put_pixel(double x, double y, int color, t_sdl *sdl)
{
	int		xnew;
	int		ynew;

	xnew = WIDTH / 2 + (int)x;
	ynew = HEIGHT / 2 - (int)y;
	sdl->pixels[xnew + ynew * WIDTH] = color;
	return (sdl->pixels);
}

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
	return(sqrt(o->x * o->x + o->y * o->y + o->z * o->z));
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

/*
** Векторное произведение
*/

t_pos		*vector_on_vector(t_pos *a, t_pos *b, t_pos *ab)
{
	ab->x = a->x * b->x;
	ab->y = a->y * b->y;
	ab->z = a->z * b->z;
	return (ab);
}

t_pos		*matrix_on_vector(double a, double b, t_pos *vec)
{
	double	x;
	double	y;
	double	z;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	vec->x = x * cos(b) + z * sin(b);
	vec->y = (x * sin(b) - z * cos(b)) * sin(a) + y * cos(a);
	vec->z = (z * cos(b) - x * sin(b)) + y * sin(a);
	return (vec);
}

/*
** Скалярное произведение векторов
*/

double		ft_dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_pos		v_plus(t_pos v1, t_pos v2)
{
	t_pos	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

t_pos		v_minus(t_pos v1, t_pos v2)
{
	t_pos	new_v;

	new_v.x = v1.x - v2.x;
	new_v.y = v1.y - v2.y;
	new_v.z = v1.z - v2.z;
	return (new_v);
}
