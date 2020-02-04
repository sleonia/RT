/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 13:25:53 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		new_elem(t_object *obj)
{
	srand(time(NULL));

	obj->type = o_sphere;
	obj->object.sphere.center = (cl_float3){rand() % 5, rand() % 3, rand() % 10};
	obj->object.sphere.radius = 2;
	// obj->material.color = (cl_float3){1, 1, 1};
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0};
	// obj->material.color = (cl_float3){rand() % 1, rand() % 1, rand() % 1};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		copy_obj(t_object *obj, t_object *scene_obj, int count_objects)
{
	int			i;

	i = -1;
	while (++i < count_objects)
	{
		obj[i] = scene_obj[i];
		// ft_memdel((void **)(&scene_obj[i]));
	}
	// ft_memdel((void **)(&scene_obj[i]);
	new_elem(&obj[i]);
}

int				realloc_objects(t_rt *rt)
{
	int			count_objects;
	t_object	*object;

	count_objects = rt->scene->count_objects;
	rt->scene->count_objects += 1;
	init_objects(&object, rt->scene->count_objects);
	copy_obj(object, rt->scene->object, count_objects);
	rt->scene->object = object;
	ft_memdel((void **)&rt->opencl);
	rt->opencl = init_cl(rt);
	// ft_memdel((void **)(rt->scene->);
	return (0);
}


static void		add_obj(t_rt *rt)
{
	realloc_objects(rt);
	
}

int				key_events(char *flag, t_rt *rt)
{
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_N)
			*flag = NEGATIVE;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_M)
			*flag = SEPIA;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			*flag = 0;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_B)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_0
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_1
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_2
			|| rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_KP_3)
			add_obj(rt);
		move(rt->sdl->event, rt->sdl, &(rt->scene->cam));
		rotation(rt->sdl->event, rt->sdl, &(rt->scene->cam));
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			save_image(rt->sdl);
		return (1);
	}
	return (0);
}
