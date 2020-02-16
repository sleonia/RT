/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_toolbar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:52:23 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/16 20:48:01 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		change_mode(int x, int y, char *flag)
{
	if ((x >= 200 && x <= 250) && (y >= 385 && y <= 410))
		*flag = BLUR;
	if ((x >= 350 && x <= 410) && (y >= 385 && y <= 410))
		*flag = 0;
	if ((x >= 200 && x <= 300) && (y >= 350 && y <= 375))
		*flag = NEGATIVE;
	if ((x >= 350 && x <= 410) && (y >= 350 && y <= 375))
		*flag = SEPIA;
}

static void		check_buttons(char *flag, int x, int y, t_rt *rt)
{
	if ((x >= 55 && x <= 350) && (y >= 705 && y <= 805))
		add_obj(88 + ft_atoi(rt->sdl->gui->textbox[New_obj]->text),
				rt->scene, rt->cl);
	if ((x >= 55 && x <= 450) && (y >= 805 && y <= 905))
		save_image(rt->sdl->screen[0]->sur->pixels);
	if ((x >= 55 && x <= 450) && (y >= 905 && y <= 1005))
		*flag = 1;
}

static bool		reset_value(int flag, t_rt *rt)
{
	for (int i = 0; i < COUNT_OF_TEXTBOX; i++)
	{
		if (i != flag)
			rt->sdl->gui->textbox[i]->on_focus = false;
	}
	return (true);
}

static bool		check_textbox(int x, int y,
							t_object **hi_lited_object, t_rt *rt)
{
	if ((x >= 185 && x <= 275) && (y >= 60 && y <= 80))
	{
		rt->sdl->gui->textbox[Phi]->on_focus = true;
		return (reset_value(Phi, rt));
	}
	if ((x >= 390 && x <= 480) && (y >= 60 && y <= 80))
	{
		rt->sdl->gui->textbox[Tetta]->on_focus = true;
		return (reset_value(Tetta, rt));
	}
	if ((x >= 180 && x <= 230) && (y >= 195 && y <= 225))
	{
		rt->sdl->gui->textbox[Id]->on_focus = true;
		return (reset_value(Id, rt));
	}
	if ((x >= 265 && x <= 360) && (y >= 195 && y <= 225))
	{
		rt->sdl->gui->textbox[Ambient]->on_focus = true;
		return (reset_value(Ambient, rt));
	}
	if ((x >= 400 && x <= 460) && (y >= 195 && y <= 225))
	{
		rt->sdl->gui->textbox[Fsaa]->on_focus = true;
		return (reset_value(Fsaa, rt));
	}
	if ((x >= 410 && x <= 430) && (y >= 710 && y <= 750))
	{
		rt->sdl->gui->textbox[New_obj]->on_focus = true;
		return (reset_value(New_obj, rt));
	}
	return (true);
}

bool			mouse_toolbar(char *flag,
							t_object **hi_lited_object,
							t_rt *rt)
{
	int			x = -1;
	int			y = -1;

	if (rt->sdl->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (rt->sdl->event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&x, &y);
			// printf("x = %d  y = %d\n", x, y);
			if (!*hi_lited_object)
			{
				if ((x >= 200 && x <= 410) && (y >= 350 && y <= 410))
					change_mode(x, y, flag);
			}
		}
	}
	check_buttons(flag, x, y, rt);
	check_textbox(x, y, hi_lited_object, rt);
	return (false);
}
