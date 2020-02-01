/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 08:04:21 by deladia           #+#    #+#             */
/*   Updated: 2020/02/01 08:04:55 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		color_negative(int color)
{
	int		red;
	int		green;
	int		blue;

	red = 255 - RED(color);
	green = 255 - GREEN(color);
	blue = 255 - BLUE(color);
	return ((red << 16) | (green << 8) | blue);
}

static void		negative(int *pixels)
{
	int			i;

	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		pixels[i] = color_negative(pixels[i]);
		++i;
	}
}

static int		color_sepia(int color)
{
	int			red;
	int			green;
	int			blue;

	red = RED(color) * 0.393 + GREEN(color) * 0.769 + BLUE(color) * 0.189;
	green = RED(color) * 0.349 + GREEN(color) * 0.686 + BLUE(color) * 0.168;
	blue = RED(color) * 0.272 + GREEN(color) * 0.534 + BLUE(color) * 0.131;
	red = ((red > 255) ? 255 : red);
	green = ((green > 255) ? 255 : green);
	blue = ((blue > 255) ? 255 : blue);
	return ((red << 16) | (green << 8) | blue);
}

static void		sepia(int *pixels)
{
	int			i;

	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		pixels[i] = color_sepia(pixels[i]);
		++i;
	}
}

int				filter(int *pixels, char flag)
{
	if (flag == NEGATIVE)
		negative(pixels);
	if (flag == SEPIA)
		sepia(pixels);
	return (0);
}
