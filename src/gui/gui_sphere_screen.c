/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sphere_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:47:21 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 18:23:58 by sleonia          ###   ########.fr       */
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
	gui_material(sdl, hi_lited_object);
	gui_buttons(sdl);
	load_textboxes(Sphere_rad, Sphere_center, sdl->gui, sdl->screen[1]->render);
	cl_float3 lox = *string_to_float_array("255 255 255");
	// printf("%f  %f  %f\n", lox.s[0], lox.s[1], lox.s[2]);
	// float_array_to_string((*hi_lited_object)->object.sphere.center);
}
