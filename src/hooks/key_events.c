/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/20 18:13:40 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			add_obj(SDL_Scancode scancode, t_scene *scene, t_cl *cl)
{
	cl_int		ret;

	ret = 0;
	if (scancode == SDL_SCANCODE_KP_1 || scancode == SDL_SCANCODE_KP_2 || scancode == SDL_SCANCODE_KP_3 || scancode == SDL_SCANCODE_KP_4 || scancode == SDL_SCANCODE_KP_5 || scancode == SDL_SCANCODE_KP_6)
	realloc_obj(scancode, scene);
	clReleaseMemObject(cl->memobjs[2]);
	if ((cl->memobjs[2] = clCreateBuffer(cl->context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_object) * scene->count_objects, scene->object, &ret))
		&& ret != 0)
		ft_error("clCreateBuffer");
}

void			change_focus(t_sdl *sdl)
{
	int			index;

	index = -1;
	if ((!sdl->screen[1]->keyboard_focus || !sdl->screen[1]->mouse_focus))
		index = 1;
	else if ((!sdl->screen[0]->keyboard_focus || !sdl->screen[0]->mouse_focus))
		index = 0;
	if (index != -1)
	{
		SDL_ShowWindow(sdl->screen[index]->win);
		SDL_RaiseWindow(sdl->screen[index]->win);
		sdl->screen[index]->shown = true;
		sdl->screen[index]->keyboard_focus = true;
		sdl->screen[index]->mouse_focus = true;
	}
}

bool			key_events(char *flag, t_object **hi_lited_object, t_rt *rt)
{
	bool		ismove;

	ismove = false;
	if (rt->sdl->screen[0]->keyboard_focus)
		ismove |= key_rt(rt->sdl->event.key.keysym.scancode, flag,
						hi_lited_object, rt);
	else if (rt->sdl->screen[1]->keyboard_focus)
		ismove |= key_toolbar(rt->sdl->event.key.keysym.scancode, flag,
							hi_lited_object, rt);
	return (ismove);
}
