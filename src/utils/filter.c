/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 08:04:21 by deladia           #+#    #+#             */
/*   Updated: 2020/02/21 08:19:49 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			negative(int *pixels)
{
	int				i;
	int				red;
	int				green;
	int				blue;

	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		red = 255 - redred(pixels[i]);
		green = 255 - greengreen(pixels[i]);
		blue = 255 - blueblue(pixels[i]);
		pixels[i] = (red << 16) | (green << 8) | blue;
	}
}

static void			sepia(int *pixels)
{
	int				i;
	int				red;
	int				green;
	int				blue;

	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		red = redred(pixels[i]) * 0.393 + greengreen(pixels[i]) * 0.769 +
				blueblue(pixels[i]) * 0.189;
		green = redred(pixels[i]) * 0.349 + greengreen(pixels[i]) * 0.686 +
				blueblue(pixels[i]) * 0.168;
		blue = redred(pixels[i]) * 0.272 + greengreen(pixels[i]) * 0.534 +
				blueblue(pixels[i]) * 0.131;
		red = ((red > 255) ? 255 : red);
		green = ((green > 255) ? 255 : green);
		blue = ((blue > 255) ? 255 : blue);
		pixels[i] = ((red << 16) | (green << 8) | blue);
	}
}

static SDL_Color	calc_color(char flag, cl_int3 color)
{
	SDL_Color		res;

	if (flag == RED_MASK)
	{
		res.r = (color.s[0] + color.s[1] + color.s[2]) / 3;
		res.g = 0;
		res.b = 0;
	}
	if (flag == GREEN_MASK)
	{
		res.r = 0;
		res.g = (color.s[0] + color.s[1] + color.s[2]) / 3;
		res.b = 0;
	}
	if (flag == BLUE_MASK)
	{
		res.r = 0;
		res.g = 0;
		res.b = (color.s[0] + color.s[1] + color.s[2]) / 3;
	}
	return (res);
}

static void			mask(char flag, int *pixels)
{
	int				i;
	SDL_Color		res;

	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		res = calc_color(flag, int_to_rgb(pixels[i]));
		pixels[i] = (res.r << 16) + (res.g << 8) + res.b;
		++i;
	}
}

int					filter(int *pixels, char flag)
{
	if (flag == NEGATIVE)
		negative(pixels);
	if (flag == SEPIA)
		sepia(pixels);
	if (flag == RED_MASK || flag == GREEN_MASK || flag == BLUE_MASK)
		mask(flag, pixels);
	return (0);
}
