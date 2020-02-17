/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sphere_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:47:21 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 21:25:40 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_sphere_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){196, 53, 0, 0};
	default_color = sdl->gui->ttf[BIG_FONT_ID]->font_color;
	sdl->gui->ttf[BIG_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){190, 35, 0, 0}, "sphere", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl->gui->ttf[BIG_FONT_ID]->font_color = default_color;
	sdl_putstr((SDL_Rect){50, 100, 0, 0}, "radius", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){380, 100, 0, 0}, "center", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	load_textboxes(Sphere_rad, Sphere_center, sdl->gui, sdl->screen[1]->render);
	gui_material(sdl, hi_lited_object);
	gui_buttons(sdl);
}
