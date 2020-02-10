/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_toolbar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:16:51 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 07:48:43 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool			key_toolbar(SDL_Scancode scancode,
						char *flag,
						t_object *hi_lited_object,
						t_rt *rt)
{
	if (hi_lited_object)
		return (false);
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (scancode == SDL_SCANCODE_1)
			rt->sdl->gui->radio_btn[0] = !rt->sdl->gui->radio_btn[0];
		if (scancode == SDL_SCANCODE_2)
			rt->sdl->gui->radio_btn[1] = !rt->sdl->gui->radio_btn[1];
		if (scancode == SDL_SCANCODE_3)
			rt->sdl->gui->radio_btn[2] = !rt->sdl->gui->radio_btn[2];
		if (scancode == SDL_SCANCODE_4)
			rt->sdl->gui->radio_btn[3] = !rt->sdl->gui->radio_btn[3];

		if (scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_1)
			change_focus(rt->sdl);
	}
	return (false);
}
