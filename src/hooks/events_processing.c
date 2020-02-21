/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:38:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 07:52:35 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static void		mask_processing(t_screen *screen)
// static void		mask_processing(SDL_Surface *sur)
// {
// 	int			i;
// 	int			k;
// 	cl_int3		color;

// 	i = -1;

// 	while (++i < HEIGHT)
// 	{
// 		k = -1;
// 		while (++k < WIDTH)
// 		{
// 			color = int_to_rgb(((int *)(sur->pixels))[k + HEIGHT * i]);
// 			((int *)(sur->pixels))[k + HEIGHT * i] = (color.s[0] + color.s[1] + color.s[2]) / 3;
// 		}
// 	}
// }

void			events_processing(char *flag,
								t_object **hi_lited_object,
								t_rt *rt)
{
	bool		ismove;

	ismove = false;
	while (SDL_PollEvent(&rt->sdl->event))
	{
		window_events(flag, rt->sdl->event, rt->sdl->screen[0]);
		window_events(flag, rt->sdl->event, rt->sdl->screen[1]);
		ismove |= key_events(flag, hi_lited_object, rt);
		ismove |= mouse_events(flag, hi_lited_object, rt);
	}
	gui_main(flag, hi_lited_object, rt->sdl, rt->scene);
	if (ismove == false)
		rt->scene->move_on = 0;
	calc_screen(&rt->scene->cam);
	create_kernel_rt(rt->cl);
	set_opencl_arg(rt->cl, rt->sdl, rt->scene);
	filter(rt->sdl->screen[0]->sur->pixels, *flag); //засунуть сюда маски
	if (*flag == BLUR && !rt->scene->move_on)
		create_kernel_blur(rt->cl, rt->sdl);
	// if (*flag == RED_MASK || *flag == GREEN_MASK || *flag == BLUE_MASK)
	// 	mask_processing(rt->sdl->screen[0]->sur);
	sdl_update(*hi_lited_object, rt->sdl);
}
