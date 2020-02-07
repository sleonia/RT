/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/07 11:50:08 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		arrows_processing(SDL_Event event, t_object *hi_lited_object)
{
	if (!hi_lited_object)
		return ;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[1] -= 0.05;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[1] -= 0.05;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[1] -= 0.05;
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_UP)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[1] += 0.05;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[1] += 0.05;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[1] += 0.05;
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[0] -= 0.05;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[0] -= 0.05;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[0] -= 0.05;
	}
if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[0] += 0.05;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[0] += 0.05;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[0] += 0.05;
	}
}

static void		add_obj(SDL_Event event, t_rt *rt)
{
	cl_int		ret;

	ret = 0;
	realloc_obj(event, rt);
	clReleaseMemObject(rt->opencl->memobjs[2]);
	if ((rt->opencl->memobjs[2] = clCreateBuffer(rt->opencl->context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_object) * rt->scene->count_objects, rt->scene->object, &ret))
		&& ret != 0)
		ft_error("clCreateBuffer");
}

int				key_events(char *flag, t_object *hi_lited_object, t_rt *rt)
{
	move(rt->sdl->event, &(rt->scene->cam), &(rt->scene->flag));
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_N)
			*flag = NEGATIVE;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_M)
			*flag = SEPIA;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_K)
			*flag = BLUR;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_H)
			rt->sdl->help_screen_flag = !rt->sdl->help_screen_flag;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_0
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_1
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_2
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_3)
			add_obj(rt->sdl->event, rt);
		rotation(rt->sdl->event, rt->sdl, &(rt->scene->cam));

		arrows_processing(rt->sdl->event, hi_lited_object);

		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			save_image(rt->sdl);
		rt->scene->move_on = 1;
		return (1);
	}
	return (0);
}
