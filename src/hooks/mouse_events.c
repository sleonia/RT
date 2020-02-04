/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:50:12 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 11:56:08 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			rotation1(int flag, t_sdl *sdl, t_cam *cam)
{
	if (sdl->event.key.keysym.scancode == (flag == 1))
	{
		cam->phi += 0.01;
		if (cam->phi > (float)M_PI - 0.00001f)
			cam->phi -= 1 * (float)M_PI;
	}
	if (sdl->event.key.keysym.scancode == (flag == 2))
	{
		cam->phi -= 0.01;
		if (cam->phi < -(float)M_PI + 0.00001f)
			cam->phi += -1 * (float)M_PI;
	}
	if (sdl->event.key.keysym.scancode == (flag == 3))
	{
		if ((cam->tetta) - 0.01 >= 0.00001f)
			cam->tetta -= 0.01;
	}
	if (sdl->event.key.keysym.scancode == (flag == 4))
	{
		if ((cam->tetta) + 0.01 <= (float)M_PI + 0.00001f)
			cam->tetta += 0.01;
	}
}


int			mouse_events(char *flag, t_sdl *sdl, t_scene *scene)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	SDL_WarpMouseInWindow(sdl->window, 640, 512);
	if (sdl->event.button.button == SDL_BUTTON_LEFT)
	{
		if (x < (WIDTH >> 1))
			rotation1(1, sdl, &(scene->cam));
		if (x > (WIDTH >> 1))
			rotation1(2, sdl, &(scene->cam));
		if (y > (HEIGHT >> 1))
			rotation1(4, sdl, &(scene->cam));
		if (y < (HEIGHT >> 1))
			rotation1(3, sdl, &(scene->cam));
		return (1);
	}
	if (sdl->event.button.button == SDL_BUTTON_RIGHT)
	{
		// realloc((void **)&(scene->object), scene->count_objects + 1);
		// scene->object[1].type = o_sphere;
		// scene->object[1].object.sphere.center = (cl_float3){1.0, -3.0, 10.0};
		// scene->object[1].object.sphere.radius = 2;
		// scene->object[1].material.color = (cl_float3){255, 0, 0};
		// scene->object[1].material.ambient = 1.0;
		// scene->object[1].material.diffuse = 0.4;
		// scene->object[1].material.specular = 50;
		// scene->object[1].material.reflection = 0;
		// scene->object[1].material.refraction = 0;
		// scene->object[1].material.texture_id = -1;
	}
	return (0);
}
