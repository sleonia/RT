/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 03:23:06 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		arrows_processing(SDL_Scancode scancode, t_object *hi_lited_object)
{
	if (!hi_lited_object)
		return ;
	if (scancode == SDL_SCANCODE_DOWN)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[1] -= 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[1] -= 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[1] -= 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[1] -= 0.17;
	}
	if (scancode == SDL_SCANCODE_UP)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[1] += 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[1] += 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[1] += 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[1] += 0.17;
	}
	if (scancode == SDL_SCANCODE_LEFT)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[0] -= 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[0] -= 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[0] -= 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[0] -= 0.17;
	}
	if (scancode == SDL_SCANCODE_RIGHT)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[0] += 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[0] += 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[0] += 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[0] += 0.17;
	}
}

static void		add_obj(SDL_Scancode scancode, t_scene *scene, t_cl *cl)
{
	cl_int		ret;

	ret = 0;
	realloc_obj(scancode, scene);
	clReleaseMemObject(cl->memobjs[2]);
	if ((cl->memobjs[2] = clCreateBuffer(cl->context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_object) * scene->count_objects, scene->object, &ret))
		&& ret != 0)
		ft_error("clCreateBuffer");
}

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
		if (scancode == SDL_SCANCODE_KP_0 || scancode == SDL_SCANCODE_KP_1
			|| scancode == SDL_SCANCODE_KP_2 || scancode == SDL_SCANCODE_KP_3
			|| scancode == SDL_SCANCODE_KP_4)
			add_obj(scancode, rt->scene, rt->cl);
		if (scancode == SDL_SCANCODE_1)
			if (!rt->sdl->screen[0]->shown)
				SDL_ShowWindow(rt->sdl->screen[0]->win);
		rotation(scancode, rt->sdl, &(rt->scene->cam));
		arrows_processing(scancode, hi_lited_object);
		if (scancode == SDL_SCANCODE_SPACE)
			save_image(rt->sdl);
		rt->scene->move_on = 1;
	}
	return (false);
}

bool			key_toolbar(SDL_Scancode scancode, char *flag, t_object *hi_lited_object, t_rt *rt)
{
	if (scancode == SDL_SCANCODE_2)
	{
		if (!rt->sdl->screen[1]->shown)
			SDL_ShowWindow(rt->sdl->screen[1]->win);
	}
	return (false);
}

bool			key_events(char *flag, t_object *hi_lited_object, t_rt *rt)
{
	bool		ismove;

	ismove = false;
	// if (rt->sdl->event.type == SDL_KEYDOWN)
	// {
		if (rt->sdl->screen[0]->keyboard_focus)
			ismove |= key_rt(rt->sdl->event.key.keysym.scancode, flag, hi_lited_object, rt);
		else if (!rt->sdl->screen[1]->keyboard_focus)
			ismove |= key_toolbar(rt->sdl->event.key.keysym.scancode, flag, hi_lited_object, rt);
	// }
	return (ismove);
}
