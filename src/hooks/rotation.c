/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:53:04 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 14:01:34 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rotation(SDL_Event event, t_sdl *sdl, t_cam *cam)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Q)
	{
		cam->phi += 0.1;
		if (cam->phi > (float)M_PI - 0.00001f)
			cam->phi -= 2 * (float)M_PI;
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_E)
	{
		cam->phi -= 0.1;
		if (cam->phi < -(float)M_PI + 0.00001f)
			cam->phi += -2 * (float)M_PI;
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Z)
	{
		if ((cam->tetta) - 0.1 >= 0.00001f)
			cam->tetta -= 0.1;
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_X)
	{
		if ((cam->tetta) + 0.1 <= (float)M_PI + 0.00001f)
			cam->tetta += 0.1;
	}
}
