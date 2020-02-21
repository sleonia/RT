/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_rt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:16:36 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 12:23:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		key_rt_2(SDL_Scancode scancode,
						t_object *select_obj,
						t_scene *scene,
						t_sdl *sdl)
{
	if (scancode == SDL_SCANCODE_B)
		SDL_ShowCursor(!SDL_ShowCursor(-1));
	if (scancode == SDL_SCANCODE_H)
		SDL_SetWindowTitle(sdl->screen[0]->win, "Peer gay!");
	if (scancode == SDL_SCANCODE_H)
		SDL_ShowSimpleMessageBox(0, "KEK", "KekWait",
								sdl->screen[0]->win);
	if (scancode == SDL_SCANCODE_Q
		|| scancode == SDL_SCANCODE_E
		|| scancode == SDL_SCANCODE_Z
		|| scancode == SDL_SCANCODE_X)
		rotation(scancode, &(scene->cam));
	if (scancode >= SDL_SCANCODE_RIGHT
		|| scancode <= SDL_SCANCODE_LEFT
		|| scancode <= SDL_SCANCODE_DOWN
		|| scancode <= SDL_SCANCODE_UP)
		arrows_processing(scancode, select_obj);
	if (scancode == SDL_SCANCODE_SPACE)
		save_image((int *)(sdl->screen[0]->sur->pixels));
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_TAB)
		change_focus(sdl);
	scene->move_on = 1;
}

bool			key_rt(SDL_Scancode scancode,
					char *flag,
					t_object **select_obj,
					t_rt *rt)
{
	SDL_ShowCursor(0);
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
		if (scancode == SDL_SCANCODE_J)
			*flag = 0;
		if (scancode == SDL_SCANCODE_O)
		{
			system("mkdir -p ./assets/photo/");
			system("imagesnap ./assets/photo/Photo_on_$(date +%m-%d-%y-%T)");
			system("afplay /System/Library/Sounds/Hero.aiff");
		}
		key_rt_2(scancode, *select_obj, rt->scene, rt->sdl);
		add_obj(scancode, rt->scene, rt->cl);
	}
	SDL_ShowCursor(1);
	return (false);
}
