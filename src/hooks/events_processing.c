/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:38:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/07 19:30:50 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			events_processing(char *flag, t_object **hi_lited_object, t_rt *rt)
{
	bool		ismove;

	ismove = false;
	while (SDL_PollEvent(&rt->sdl->event))
	{
		if (rt->sdl->event.type == SDL_QUIT)
			*flag = 1;
		ismove |= key_events(flag, *hi_lited_object, rt);
		ismove |= mouse_events(flag, rt->sdl, hi_lited_object, rt->scene);
	}
	if (ismove == false)
		rt->scene->move_on = 0;
	calc_screen(&rt->scene->cam);
	create_kernel_rt(rt->opencl, rt->scene);
	set_opencl_arg(rt->opencl, rt->sdl, rt->scene);
	filter(rt->sdl->sur->pixels, *flag);
	if (*flag == BLUR && !rt->scene->move_on)
		create_kernel_blur(rt->opencl, rt->sdl);
	sdl_update(rt->sdl);
}
