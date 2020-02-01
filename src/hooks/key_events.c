/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 04:56:56 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			key_events(char *quit, t_sdl *sdl,
								t_scene *scene, t_cl *cl)
{
	if (sdl->event.type == SDL_KEYDOWN)
	{
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			*quit = 1;
		move(sdl->event, sdl, &(scene->cam));
		rotation(sdl->event, sdl, &(scene->cam));
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			;//save_helper(sdl);
	}
}
