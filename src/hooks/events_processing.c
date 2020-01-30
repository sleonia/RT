/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:38:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/31 01:36:35 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			events_processing(char *quit, t_sdl *sdl,
								t_scene *scene, t_cl *cl)
{
	while (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.type == SDL_QUIT)
			*quit = 1;
		key_events(quit, sdl, scene, cl);
		// mouse_events(quit, sdl, scene, cl);
	}
}
