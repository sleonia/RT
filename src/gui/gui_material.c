/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:54:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 11:37:00 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			gui_material(t_sdl *sdl)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){189, 171, 135, 0};
	default_color = sdl->gui->ttf[NORMAL_FONT_ID]->font_color;
	sdl->gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){50, 350, 0, 0}, "color",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 400, 0, 0}, "ambient",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 450, 0, 0}, "diffuse",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 500, 0, 0}, "specular",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 550, 0, 0}, "reflection",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 600, 0, 0}, "refraction",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){50, 650, 0, 0}, "texture_id",
				sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl->gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	load_textboxes(Mtrl_Color, Mtrl_texture_id,
				sdl->gui, sdl->screen[1]->render);
}
