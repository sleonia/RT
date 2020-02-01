/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 15:34:15 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				key_events(char *flag, t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.type == SDL_KEYDOWN)
	{
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_N)
			*flag = NEGATIVE;
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_M)
			*flag = SEPIA;
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			*flag = 0;
		move(sdl->event, sdl, &(scene->cam));
		rotation(sdl->event, sdl, &(scene->cam));
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			save_image(sdl);
		return (1);
	}
	return (0);
}
