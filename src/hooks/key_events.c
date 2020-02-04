/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 12:47:29 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		add_obj(t_rt *rt)
{
	// rt->opencl
}

int				key_events(char *flag, t_rt *rt)
{
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_N)
			*flag = NEGATIVE;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_M)
			*flag = SEPIA;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			*flag = 0;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_0
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_1
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_2
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_3)
			add_obj(rt);
		move(rt->sdl->event, rt->sdl, &(rt->scene->cam));
		rotation(rt->sdl->event, rt->sdl, &(rt->scene->cam));
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			save_image(rt->sdl);
		return (1);
	}
	return (0);
}
