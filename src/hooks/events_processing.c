/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:38:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/02 20:40:39 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			events_processing(char *flag, t_sdl *sdl,
								t_scene *scene, t_cl *cl)
{
	if (sdl->event.type == SDL_QUIT)
			*flag = 1;
	if (key_events(flag, sdl, scene) || mouse_events(flag, sdl, scene))
	{
		calc_screen(&scene->cam);
		set_opencl_arg(cl, sdl, scene);
		filter(sdl->pixels, *flag);
		sdl_update(sdl);
	}
}
