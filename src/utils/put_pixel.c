/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:02:14 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 04:26:09 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			*put_pixel(double x, double y, int color, t_sdl *sdl)
{
	int		xnew;
	int		ynew;

	xnew = WIDTH / 2 + (int)x;
	ynew = HEIGHT / 2 - (int)y;
	sdl->pixels[xnew + ynew * WIDTH] = color;
	return (sdl->pixels);
}
