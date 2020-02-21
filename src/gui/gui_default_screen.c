/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_default_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:44:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 12:00:37 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			gui_skybox(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 175, 0, 0}, "Skybox", gui->ttf[BIG_FONT_ID], sur);
	sdl_putstr((SDL_Rect){200, 155, 0, 0}, "id",
				gui->ttf[NORMAL_FONT_ID], sur);
	sdl_putstr((SDL_Rect){265, 155, 0, 0}, "ambient",
				gui->ttf[NORMAL_FONT_ID], sur);
	sdl_putstr((SDL_Rect){400, 155, 0, 0}, "fsaa",
				gui->ttf[NORMAL_FONT_ID], sur);
}

void			gui_camera(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 35, 0, 0}, "Camera", gui->ttf[BIG_FONT_ID], sur);
	sdl_putstr((SDL_Rect){200, 15, 0, 0}, "phi",
				gui->ttf[NORMAL_FONT_ID], sur);
	sdl_putstr((SDL_Rect){400, 15, 0, 0}, "tetta",
				gui->ttf[NORMAL_FONT_ID], sur);
}

void			gui_default_screen(char *flag, t_sdl *sdl)
{
	sdl->gui->ttf[NORMAL_FONT_ID]->font_color = (SDL_Color){255, 255, 255, 0};
	gui_camera(sdl->gui, sdl->screen[1]->sur);
	gui_skybox(sdl->gui, sdl->screen[1]->sur);
	gui_mode(flag, sdl->gui, sdl->screen[1]->sur);
	gui_buttons(sdl);
	load_textboxes(Phi, New_obj, sdl->gui, sdl->screen[1]->render);
}
