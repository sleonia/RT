/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cylinder_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:56:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 14:41:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_cylinder_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){196, 53, 0, 0};
	default_color = sdl->gui->ttf[BIG_FONT_ID]->font_color;
	sdl->gui->ttf[BIG_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){180, 35, 0, 0}, "cylinder", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl->gui->ttf[BIG_FONT_ID]->font_color = default_color;
	sdl_putstr((SDL_Rect){190, 300, 0, 0}, "axis", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 400, 0, 0}, "center", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 500, 0, 0}, "length", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 600, 0, 0}, "radius", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	gui_material(sdl, hi_lited_object);
	gui_buttons(sdl);
	load_textboxes(Cylinder_axis, Cylinder_rad, sdl->gui, sdl->screen[1]->render);
}
