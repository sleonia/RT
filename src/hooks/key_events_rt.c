/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_rt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:16:36 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 07:18:18 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool			key_rt(SDL_Scancode scancode, char *flag, t_object *hi_lited_object, t_rt *rt)
{
	move(rt->sdl->event, &(rt->scene->cam), &(rt->scene->flag));
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (scancode == SDL_SCANCODE_N)
			*flag = NEGATIVE;
		if (scancode == SDL_SCANCODE_M)
			*flag = SEPIA;
		if (scancode == SDL_SCANCODE_K)
			*flag = BLUR;
		if (scancode == SDL_SCANCODE_B)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		if (scancode == SDL_SCANCODE_H)
			SDL_SetWindowTitle(rt->sdl->screen[0]->win, "Peer gay!");
		if (scancode == SDL_SCANCODE_H)
			SDL_ShowSimpleMessageBox(0, "KEK", "KekWait", rt->sdl->screen[0]->win);
		if (scancode == SDL_SCANCODE_J)
			*flag = 0;
		if (scancode >= SDL_SCANCODE_KP_0 && scancode <= SDL_SCANCODE_KP_4)
			add_obj(scancode, rt->scene, rt->cl);
		rotation(scancode, rt->sdl, &(rt->scene->cam));
		arrows_processing(scancode, hi_lited_object);
		if (scancode == SDL_SCANCODE_SPACE)
			save_image((int *)(rt->sdl->screen[0]->sur->pixels));
		rt->scene->move_on = 1;
	}
	return (false);
}
