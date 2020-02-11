/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:54:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/12 00:36:03 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_background(int *pixels)
{
	int		i;
	int		k;

	i = -1;
	while (++i < HEIGHT)
	{
		k = -1;
		while (++k < 500)
			(pixels)[i * 500 + k] = 0x2C3852;
	}
}

void		gui_main(char *flag, t_object **hi_lited_object, t_sdl *sdl)
{
	draw_background(((int *)(sdl->screen[1]->sur->pixels)));
	if (!*hi_lited_object)
		gui_default_screen(flag, hi_lited_object, sdl);
	// else if ((*hi_lited_object)->type == o_sphere)
	// 	sdl_putstr(100, 100, "0", sdl);
	// else if ((*hi_lited_object)->type == o_cylinder)
	// 	sdl_putstr(100, 100, "1", sdl);
	// else if ((*hi_lited_object)->type == o_cone)
	// 	sdl_putstr(100, 100, "2", sdl);
	// else if ((*hi_lited_object)->type == o_plane)
	// 	sdl_putstr(100, 100, "3", sdl);
	// else if ((*hi_lited_object)->type == o_parab)
	// 	sdl_putstr(100, 100, "4", sdl);
}
