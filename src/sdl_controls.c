/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:11:54 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 14:12:04 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sdl_control_6(t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_O)
	{
		if (!scene->off->directional)
			scene->off->directional = 1;
		else
			scene->off->directional = 0;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_U)
	{
		if (!scene->off->reflect)
			scene->off->reflect = 1;
		else
			scene->off->reflect = 0;
		trace_start(sdl, scene);
	}
}

void		sdl_control_5(t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_W)
	{
		scene->cam->position.z += 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_S)
	{
		scene->cam->position.z -= 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_A)
	{
		scene->cam->position.x -= 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_D)
	{
		scene->cam->position.x += 0.1;
		trace_start(sdl, scene);
	}
}

void		sdl_control_4(t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_P)
	{
		if (!scene->off->point)
			scene->off->point = 1;
		else
			scene->off->point = 0;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_I)
	{
		if (!scene->off->ambient)
			scene->off->ambient = 1;
		else
			scene->off->ambient = 0;
		trace_start(sdl, scene);
	}
}

void		sdl_control_3(t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_X &&
		scene->cam->a >= -90)
	{
		scene->cam->a -= 10;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Q &&
		scene->cam->b >= -90)
	{
		scene->cam->b -= 10;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_E &&
		scene->cam->b <= 90)
	{
		scene->cam->b += 10;
		trace_start(sdl, scene);
	}
}

void		sdl_control_2(t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_R)
	{
		scene->cam->position.y += 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_F)
	{
		scene->cam->position.y -= 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Z &&
		scene->cam->a <= 90)
	{
		scene->cam->a += 10;
		trace_start(sdl, scene);
	}
}
