/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/05 22:39:54 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_loop(t_rt *rt)
{
	char			flag;
	SDL_Event		event;
	Uint32			timeout;
	t_object		*hi_lited_object;

	hi_lited_object = NULL;
	flag = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_update(rt->sdl);
	while (flag != 1)
	{
		timeout = SDL_GetTicks() + 30;
		while (SDL_PollEvent(&rt->sdl->event)
			&& (rt->sdl->event.type == SDL_KEYUP
				|| !SDL_TICKS_PASSED(SDL_GetTicks(), timeout)))
		{
			events_processing(&flag, &hi_lited_object, rt);
		}
		if (rt->sdl->event.type == SDL_QUIT)
			break ;
	}
	sdl_quit(rt->sdl);
}
