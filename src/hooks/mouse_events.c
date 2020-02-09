/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:50:12 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/09 02:25:24 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			mouse_rotation(t_cam *cam, int x, int y)
{
	float d_tetta;
	d_tetta = (y - HEIGHT / 2) * 0.001f;
	cam->phi -= (x - WIDTH / 2) * 0.001f;
	if (cam->phi > (float)M_PI - 0.00001f)
		cam->phi -= 1 * (float)M_PI;
	if (cam->phi < -(float)M_PI + 0.00001f)
		cam->phi += -1 * (float)M_PI;
	if (d_tetta < 0  && (cam->tetta) + d_tetta >= 0.00001f)
		cam->tetta += d_tetta;
	if (d_tetta > 0 && (cam->tetta) + d_tetta <= (float)M_PI + 0.00001f)
		cam->tetta += d_tetta;
}

bool			mouse_toolbar(char *flag, t_sdl *sdl, t_object **hi_lited_object, t_scene *scene)
{
	int			i;
	int			x = -1;
	int			y = -1;

	if (sdl->event.button.button == SDL_BUTTON_LEFT)
		SDL_GetMouseState(&x, &y);
	i = -1;
	// while (++i < 4)
	// {
	if (x != -1 && y != -1)
		printf("x = %d   y = %d\n", x ,y);
	// if ((x >= 70 && x <= 120) && (y >= 0 && y <= 36))
	if ((x >= 70 && x <= 120) && (y >= 50 && y <= 86))
	{
		sdl->gui->radio_btn[0] = !sdl->gui->radio_btn[0];
	}
	if ((x >= 70 && x <= 120) && (y >= 100 && y <= 100 + 36))
	{
		sdl->gui->radio_btn[1] = !sdl->gui->radio_btn[1];
	}
	if ((x >= 70 && x <= 120) && (y >= 150 && y <= 150 + 36))
	{
		sdl->gui->radio_btn[2] = !sdl->gui->radio_btn[2];
	}
	if ((x >= 70 && x <= 120) && (y >= 200 && y <= 200 + 36))
	{
		sdl->gui->radio_btn[3] = !sdl->gui->radio_btn[3];
	}
	// }
	// if (flag)
		// return (false);
	// if ()
	return (false);
}

bool			mouse_rt(char *flag, t_sdl *sdl, t_object **hi_lited_object, t_scene *scene)
{
	int			x;
	int			y;

	SDL_GetMouseState(&x, &y);
	if (sdl->event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_WarpMouseInWindow(sdl->screen[0]->win, 640, 512);
			mouse_rotation(&(scene->cam), x, y);
		scene->move_on = 1;
		return (true);
	}
	if (sdl->event.button.button == SDL_BUTTON_RIGHT)
	{
		if ((*hi_lited_object = get_object(scene, x, y)) != NULL)
			return (true);
	}
	return (false);
}

bool			mouse_events(char *flag, t_sdl *sdl, t_object **hi_lited_object, t_scene *scene)
{
	// int			x;
	// int			y;

	// SDL_GetMouseState(&x, &y);
	if (sdl->screen[0]->mouse_focus)
		return (mouse_rt(flag, sdl, hi_lited_object, scene));
	else if (sdl->screen[1]->mouse_focus)
		return (mouse_toolbar(flag, sdl, hi_lited_object, scene));
	return (false);
}