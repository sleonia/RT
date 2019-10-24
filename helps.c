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

int 		*put_pixel(double x, double y, int color, t_sdl *sdl)
{
	int		xnew;
	int		ynew;

	xnew = WIDTH / 2 + (int)x;
	ynew = HEIGHT / 2 - (int)y;
//	printf("%d \n", (int)xnew + (int)ynew * WIDTH);
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
** Скалярное произведение векторов
*/

double		dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
