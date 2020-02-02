/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/02 20:43:56 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_loop(t_sdl *sdl, t_scene *scene, t_cl *cl)
{
	char	flag;
	flag = 0;
	SDL_Event		event;
	Uint32			timeout;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_update(sdl);
	while (flag != 1)
	{
		timeout = SDL_GetTicks() + 30;
		while (SDL_PollEvent(&sdl->event) && (sdl->event.type == SDL_KEYUP
			|| !SDL_TICKS_PASSED(SDL_GetTicks(), timeout)))
		{
			events_processing(&flag, sdl, scene, cl);
		}
		if (sdl->event.type == SDL_QUIT)
			break ;
	}
	sdl_quit(sdl);
}
