/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:54:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 08:01:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_background(int color, int *pixels)
{
	int		i;
	int		k;

	i = -1;
	while (++i < HEIGHT)
	{
		k = -1;
		while (++k < TOOL_SCREEN_WIDTH)
			(pixels)[i * TOOL_SCREEN_WIDTH + k] = color;
	}
}

void		gui_main(char *flag,
					t_object **hi_lited_object,
					t_rt *rt)
{
	if (rt->sdl->screen[1]->keyboard_focus)
	{
		draw_background(0x2C3852, ((int *)(rt->sdl->screen[1]->sur->pixels)));
		if (!*hi_lited_object)
			gui_default_screen(flag, rt->sdl);
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
	else
	{
		draw_background(0x0, ((int *)(rt->sdl->screen[1]->sur->pixels)));
		set_value_in_textbox(rt->scene, rt->sdl->gui);
		render_surface((SDL_Rect){0, 0, 0, 0},
					(SDL_Rect){-70, 50,
							TOOL_SCREEN_WIDTH + 160,
							TOOL_SCREEN_HEIGHT - 100},
					rt->sdl->gui->headband,
					rt->sdl);
	}
}
