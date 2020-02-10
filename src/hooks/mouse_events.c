/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:50:12 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 11:13:05 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			mouse_rotation(t_cam *cam, int x, int y)
{
	float		d_tetta;
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


bool			mouse_events(char *flag,
							t_object **hi_lited_object,
							t_rt *rt)
{
	// int			x;
	// int			y;

	// SDL_GetMouseState(&x, &y);
	if (rt->sdl->screen[0]->mouse_focus)
		return (mouse_rt(flag, rt->sdl, hi_lited_object, rt->scene));
	else if (rt->sdl->screen[1]->mouse_focus)
		return (mouse_toolbar(flag, hi_lited_object, rt));
	return (false);
}