/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_torus_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:59:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 19:51:48 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_torus_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){196, 53, 0, 0};
	default_color = sdl->gui->ttf[BIG_FONT_ID]->font_color;
	sdl->gui->ttf[BIG_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){210, 35, 0, 0}, "torus", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl->gui->ttf[BIG_FONT_ID]->font_color = default_color;

	sdl_putstr((SDL_Rect){360, 100, 0, 0}, "axis", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){360, 200, 0, 0}, "center", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 100, 0, 0}, "bigr", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 200, 0, 0}, "r", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	// gui_material(sdl, hi_lited_object);
	gui_buttons(sdl);
	load_textboxes(Torus_axis, Torus_r, sdl->gui, sdl->screen[1]->render);
}
