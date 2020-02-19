/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_plane_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:58:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 19:51:42 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_plane_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){196, 53, 0, 0};
	default_color = sdl->gui->ttf[BIG_FONT_ID]->font_color;
	sdl->gui->ttf[BIG_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){200, 35, 0, 0}, "plane", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl->gui->ttf[BIG_FONT_ID]->font_color = default_color;

	sdl_putstr((SDL_Rect){50, 100, 0, 0}, "distance", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);	
	sdl_putstr((SDL_Rect){360, 100, 0, 0}, "axis", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	// gui_material(sdl, hi_lited_object);
	gui_buttons(sdl);
	load_textboxes(Plane_axis, Plane_tan, sdl->gui, sdl->screen[1]->render);
}
