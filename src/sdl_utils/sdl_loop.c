/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 15:14:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_loop(t_rt *rt)
{
	char			flag;
	SDL_Event		event;
	Uint32			timeout;

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
			events_processing(&flag, rt);
		}
		if (rt->sdl->event.type == SDL_QUIT)
			break ;
	}
	sdl_quit(rt->sdl);
}
