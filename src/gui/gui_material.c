/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:54:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 21:25:04 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gui_material(t_sdl *sdl, t_object **hi_lited_object)
{
	sdl_putstr((SDL_Rect){100, 250, 0, 0}, "color", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 300, 0, 0}, "ambient", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 350, 0, 0}, "diffuse", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 400, 0, 0}, "specular", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 450, 0, 0}, "reflection", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 500, 0, 0}, "refraction", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 550, 0, 0}, "texture_id", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){100, 600, 0, 0}, "texture", sdl->gui->ttf[NORMAL_FONT_ID], sdl->screen[1]->sur);
	load_textboxes(Mtrl_Color, Mtrl_Texture, sdl->gui, sdl->screen[1]->render);
}
