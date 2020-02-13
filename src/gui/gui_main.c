/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:54:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/13 09:04:19 by sleonia          ###   ########.fr       */
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

void	resize_surface(SDL_Rect srcrect, SDL_Rect dstrect,
					SDL_Surface *texture, t_sdl *sdl)
{
	SDL_BlitScaled(texture, NULL, sdl->screen[1]->sur, &dstrect);
}

void				render_surface(SDL_Rect srcrect, SDL_Rect dstrect,
								SDL_Surface *surface, t_sdl *sdl)
{
	SDL_Surface		*copy_texture;

	copy_texture = SDL_DuplicateSurface(surface);
	resize_surface(srcrect,
					dstrect,
					copy_texture, sdl);
	SDL_BlitSurface(sdl->screen[1]->sur, NULL, copy_texture, NULL);
	SDL_FreeSurface(copy_texture);
}

void		gui_main(char *flag, t_object **hi_lited_object, t_sdl *sdl)
{
	if (sdl->screen[1]->keyboard_focus)
	{
		draw_background(0x2C3852, ((int *)(sdl->screen[1]->sur->pixels)));
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
	else
	{
		draw_background(0x0, ((int *)(sdl->screen[1]->sur->pixels)));
		render_surface((SDL_Rect){0, 0, 0, 0}, (SDL_Rect){-70, 50, TOOL_SCREEN_WIDTH + 160, TOOL_SCREEN_HEIGHT - 100},  sdl->gui->headband, sdl);
		// SDL_BlitSurface(sur_img, &(SDL_Rect){0, -50, TOOL_SCREEN_WIDTH, TOOL_SCREEN_HEIGHT}, sdl->screen[1]->sur, NULL);
	}
}
