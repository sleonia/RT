/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_toolbar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:52:23 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/15 11:08:49 by sleonia          ###   ########.fr       */
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
	// int			type_obj;

	// type_obj = 
	if ((x >= 55 && x <= 450) && (y >= 705 && y <= 805))
	{
		add_obj(89 + ft_atoi(rt->sdl->gui->textbox[New_obj]->text), rt->scene, rt->cl);
	}
	if ((x >= 55 && x <= 450) && (y >= 805 && y <= 905))
		save_image(rt->sdl->screen[0]->sur->pixels);
	if ((x >= 55 && x <= 450) && (y >= 905 && y <= 1005))
		*flag = 1;
}

bool			mouse_toolbar(char *flag,
							t_object **hi_lited_object,
							t_rt *rt)
{
	int			x = -1;
	int			y = -1;

	if (rt->sdl->event.button.button == SDL_BUTTON_LEFT)
		SDL_GetMouseState(&x, &y);
	if (!*hi_lited_object)
	{
		if ((x >= 200 && x <= 410) && (y >= 350 && y <= 410))
			change_mode(x, y, flag);
	}
	check_buttons(flag, x, y, rt);
	return (false);
}
