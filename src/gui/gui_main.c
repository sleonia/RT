/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:54:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/20 17:53:44 by sleonia          ###   ########.fr       */
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
					t_sdl *sdl,
					t_scene *scene)
{
	if (sdl->screen[1]->keyboard_focus)
	{
		draw_background(0x2C3852, ((int *)(sdl->screen[1]->sur->pixels)));
		if (!*hi_lited_object)
			gui_default_screen(flag, sdl);
		else if ((*hi_lited_object)->type == o_sphere)
		{
			gui_sphere_screen(sdl, hi_lited_object);
			if ((*hi_lited_object)->type != o_sphere)
				printf("lox\n");
		}
		else if ((*hi_lited_object)->type == o_cylinder)
			gui_cylinder_screen(sdl, hi_lited_object);
		else if ((*hi_lited_object)->type == o_cone)
			gui_cone_screen(sdl, hi_lited_object);
		else if ((*hi_lited_object)->type == o_plane)
			gui_plane_screen(sdl, hi_lited_object);
		else if ((*hi_lited_object)->type == o_parab)
			gui_parab_screen(sdl, hi_lited_object);
		else if ((*hi_lited_object)->type == o_torus)
			gui_torus_screen(sdl, hi_lited_object);
		else
		{
			printf("%f\n", (*hi_lited_object)->material.specular);
			// if (!hi_lited_object)
				// printf("lox\n");
		}
		
	}
	else
	{
		draw_background(0x0, ((int *)(sdl->screen[1]->sur->pixels)));
		set_textbox_value(scene, hi_lited_object, sdl->gui);
		render_surface((SDL_Rect){0, 0, 0, 0}, (SDL_Rect){-70, 50,
			TOOL_SCREEN_WIDTH + 160, TOOL_SCREEN_HEIGHT - 100},
			sdl->gui->headband, sdl);
	}
}
