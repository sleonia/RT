/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/20 18:01:05 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_loop(t_rt *rt)
{
	char			flag;
	t_object		*hi_lited_object;

	hi_lited_object = NULL;
	flag = 0;
	// SDL_ShowCursor(0);
	sdl_update(hi_lited_object, rt->sdl);
	SDL_ShowWindow(rt->sdl->screen[0]->win);
	SDL_RaiseWindow(rt->sdl->screen[0]->win);
	rt->sdl->screen[0]->shown = true;
	SDL_StartTextInput();
	while (flag != 1)
	{
		events_processing(&flag, &hi_lited_object, rt);
	}
	SDL_StopTextInput();
	sdl_quit(rt->sdl);
}
