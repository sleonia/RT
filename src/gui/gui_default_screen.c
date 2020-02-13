/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_default_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:44:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/13 07:13:23 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		gui_mode2(char *flag, t_gui *gui, SDL_Surface *sur)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){255, 0, 0, 0};
	default_color = gui->ttf[0]->font_color;
	if (*flag == BLUR)
	{
		gui->ttf[0]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){200, 375, 0, 0}, "Blur", gui->ttf[0], sur);
		gui->ttf[0]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){200, 375, 0, 0}, "Blur", gui->ttf[0], sur);
	if (*flag == 0)
	{
		gui->ttf[0]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){350, 375, 0, 0}, "None", gui->ttf[0], sur);
		gui->ttf[0]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){350, 375, 0, 0}, "None", gui->ttf[0], sur);
}

void			gui_mode(char *flag, t_gui *gui, SDL_Surface *sur)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){255, 0, 0, 0};
	default_color = gui->ttf[0]->font_color;
	sdl_putstr((SDL_Rect){15, 315, 0, 0}, "Mode", gui->ttf[1], sur);
	if (*flag == NEGATIVE)
	{
		gui->ttf[0]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){200, 345, 0, 0}, "Negative", gui->ttf[0], sur);
		gui->ttf[0]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){200, 345, 0, 0}, "Negative", gui->ttf[0], sur);
	if (*flag == SEPIA)
	{
		gui->ttf[0]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){350, 345, 0, 0}, "Sepia", gui->ttf[0], sur);
		gui->ttf[0]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){350, 345, 0, 0}, "Sepia", gui->ttf[0], sur);
	gui_mode2(flag, gui, sur);
}

void			gui_skybox(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 175, 0, 0}, "Skybox", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 155, 0, 0}, "id", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){265, 155, 0, 0}, "ambient", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){400, 155, 0, 0}, "fsaa", gui->ttf[0], sur);
}

void			gui_camera(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 35, 0, 0}, "Camera", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 15, 0, 0}, "phi", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){265, 15, 0, 0}, "position", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){400, 15, 0, 0}, "tetta", gui->ttf[0], sur);
}



void			gui_default_screen(char *flag,
								t_object **hi_lited_object,
								t_sdl *sdl)
{

	sdl->gui->ttf[0]->font_color = (SDL_Color){255, 255, 255, 0};
	gui_camera(sdl->gui, sdl->screen[1]->sur);
	gui_skybox(sdl->gui, sdl->screen[1]->sur);
	gui_mode(flag, sdl->gui, sdl->screen[1]->sur);
	gui_buttons(sdl);

	load_from_rendered_text(sdl->gui->textbox[0], sdl->gui->textbox[0]->text, sdl->screen[1]->render, sdl->gui->ttf[2]->font);
}
