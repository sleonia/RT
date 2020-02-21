/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:56:54 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 12:11:02 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		gui_mode4(SDL_Color highlighted_color, char *flag,
						t_gui *gui, SDL_Surface *sur)
{
	SDL_Color	default_color;

	default_color = gui->ttf[NORMAL_FONT_ID]->font_color;
	if (*flag == BLUE_MASK)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){200, 435, 0, 0}, "Blue_mask",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){200, 435, 0, 0}, "Blue_mask",
					gui->ttf[NORMAL_FONT_ID], sur);
}

static void		gui_mode3(SDL_Color highlighted_color, char *flag,
						t_gui *gui, SDL_Surface *sur)
{
	SDL_Color	default_color;

	default_color = gui->ttf[NORMAL_FONT_ID]->font_color;
	if (*flag == RED_MASK)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){200, 405, 0, 0}, "Red_mask",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){200, 405, 0, 0}, "Red_mask",
					gui->ttf[NORMAL_FONT_ID], sur);
	if (*flag == GREEN_MASK)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){350, 405, 0, 0}, "Green_mask",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){350, 405, 0, 0}, "Green_mask",
					gui->ttf[NORMAL_FONT_ID], sur);
}

static void		gui_mode2(SDL_Color highlighted_color, char *flag,
						t_gui *gui, SDL_Surface *sur)
{
	SDL_Color	default_color;

	default_color = gui->ttf[NORMAL_FONT_ID]->font_color;
	if (*flag == BLUR)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){200, 375, 0, 0}, "Blur",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){200, 375, 0, 0}, "Blur",
					gui->ttf[NORMAL_FONT_ID], sur);
	if (*flag == 0)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){350, 375, 0, 0}, "None",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){350, 375, 0, 0}, "None",
					gui->ttf[NORMAL_FONT_ID], sur);
}

static void		gui_mode1(SDL_Color highlighted_color, char *flag,
						t_gui *gui, SDL_Surface *sur)
{
	SDL_Color	default_color;

	default_color = gui->ttf[NORMAL_FONT_ID]->font_color;
	sdl_putstr((SDL_Rect){15, 315, 0, 0}, "Mode", gui->ttf[BIG_FONT_ID], sur);
	if (*flag == NEGATIVE)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){200, 345, 0, 0}, "Negative",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){200, 345, 0, 0}, "Negative",
					gui->ttf[NORMAL_FONT_ID], sur);
	if (*flag == SEPIA)
	{
		gui->ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
		sdl_putstr((SDL_Rect){350, 345, 0, 0}, "Sepia",
					gui->ttf[NORMAL_FONT_ID], sur);
		gui->ttf[NORMAL_FONT_ID]->font_color = default_color;
	}
	else
		sdl_putstr((SDL_Rect){350, 345, 0, 0}, "Sepia",
					gui->ttf[NORMAL_FONT_ID], sur);
}

void			gui_mode(char *flag, t_gui *gui, SDL_Surface *sur)
{
	gui_mode1((SDL_Color){255, 0, 0, 0}, flag, gui, sur);
	gui_mode2((SDL_Color){255, 0, 0, 0}, flag, gui, sur);
	gui_mode3((SDL_Color){255, 0, 0, 0}, flag, gui, sur);
	gui_mode4((SDL_Color){255, 0, 0, 0}, flag, gui, sur);
}
