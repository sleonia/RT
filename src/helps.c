/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:59:13 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 17:51:45 by deladia          ###   ########.fr       */
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
	t_pos	pos;

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
** Векторное произведение
*/

t_pos		*vector_on_vector(t_pos *a, t_pos *b, t_pos *ab)
{
	ab->x = a->x * b->x;
	ab->y = a->y * b->y;
	ab->z = a->z * b->z;
	return (ab);
}
