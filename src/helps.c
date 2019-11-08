/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:59:13 by deladia           #+#    #+#             */
/*   Updated: 2019/10/31 16:38:53 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			*put_pixel(double x, double y, int color, t_sdl *sdl)
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

t_pos		insert(int x, int y, int z)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
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
	double	b_to_rad;
	double	a_to_rad;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	b_to_rad = (b * M_PI) / 180;
	a_to_rad = (a * M_PI) / 180;
	vec->x = x * cos(b_to_rad) + z * sin(b_to_rad);
	vec->y = (x * sin(b_to_rad) - z * cos(b_to_rad)) * sin(a_to_rad) + y
			* cos(a_to_rad);
	vec->z = ((z * cos(b_to_rad) - x * sin(b_to_rad)) * cos(a_to_rad)) + y
			* sin(a_to_rad);
	return (vec);
}

/*
** Скалярное произведение векторов
*/

t_pos		vector_normalize(t_pos *a)
{
	float	len;
	t_pos	vec;

	vec = *a;
	len = vector_len(a);
	if (len == 0)
		return (vec);
	vec = vector_on_number(a, 1 / len);
	return (vec);
}

double		dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

