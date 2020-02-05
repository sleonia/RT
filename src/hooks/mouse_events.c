/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:50:12 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/05 15:40:09 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			mouse_rotation(int flag, t_sdl *sdl, t_cam *cam)
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
	int			x;
	int			y;
	t_object	*obj;

	SDL_GetMouseState(&x, &y);		
	if (sdl->event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_WarpMouseInWindow(sdl->window, 640, 512);
		if (x < (WIDTH >> 1))
			mouse_rotation(1, sdl, &(scene->cam));
		if (x > (WIDTH >> 1))
			mouse_rotation(2, sdl, &(scene->cam));
		if (y > (HEIGHT >> 1))
			mouse_rotation(4, sdl, &(scene->cam));
		if (y < (HEIGHT >> 1))
			mouse_rotation(3, sdl, &(scene->cam));
		scene->move_on = 1;
		return (1);
	}
	if (sdl->event.button.button == SDL_BUTTON_RIGHT)
	{
		if ((obj = get_object(scene, x, y)) != NULL)
		{
			scene->hi_lited_object = obj;
			// printf("%d\n", obj->type);
			// if (obj->type == o_sphere)
				// obj->material.color = (cl_float3){1.f, 1.f, 1.f};
		}
		else
			scene->hi_lited_object = NULL;
		return (1);
	}
	return (0);
}
