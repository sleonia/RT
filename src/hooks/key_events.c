/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/02 19:57:07 by sleonia          ###   ########.fr       */
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
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		move(sdl->event, sdl, &(scene->cam));
		rotation(sdl->event, sdl, &(scene->cam));
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			save_image(sdl);
		return (1);
	}
	return (0);
}
