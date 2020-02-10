/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:38:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 09:54:16 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			events_processing(char *flag, t_object **hi_lited_object, t_rt *rt)
{
	bool		ismove;

	ismove = false;
	while (SDL_PollEvent(&rt->sdl->event))
	{
		window_events(flag, rt->sdl->event, rt->sdl->screen[0]);
		window_events(flag, rt->sdl->event, rt->sdl->screen[1]);
		ismove |= key_events(flag, *hi_lited_object, rt);
		ismove |= mouse_events(flag, hi_lited_object, rt);
	}
	if (ismove == false)
		rt->scene->move_on = 0;
	calc_screen(&rt->scene->cam);
	create_kernel_rt(rt->cl, rt->scene);
	set_opencl_arg(rt->cl, rt->sdl, rt->scene);
	filter(rt->sdl->screen[0]->sur->pixels, *flag);
	if (*flag == BLUR && !rt->scene->move_on)
		create_kernel_blur(rt->cl, rt->sdl);
	sdl_update(flag, hi_lited_object, rt->sdl);
}
