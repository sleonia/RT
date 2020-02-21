/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_toolbar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:52:23 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 12:23:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool			mouse_toolbar(char *flag,
							t_object **select_obj,
							t_rt *rt)
{
	int			x;
	int			y;

	x = -1;
	y = -1;
	if (rt->sdl->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (rt->sdl->event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&x, &y);
			if (!*select_obj)
			{
				if ((x >= 200 && x <= 410) && (y >= 350 && y <= 465))
					change_mode(x, y, flag);
			}
		}
		check_buttons(x, y, select_obj, rt);
		check_textbox(x, y, select_obj, rt->sdl->gui->textbox);
		if (rt->sdl->event.button.button == SDL_BUTTON_RIGHT)
			change_focus(rt->sdl);
	}
	return (false);
}
