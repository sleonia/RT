/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 14:57:43 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		new_sphere(t_object *obj)
{
	srand(time(NULL));
	obj->type = o_sphere;
	obj->object.sphere.center = (cl_float3){rand() % 5, rand() % 3, rand() % 10};
	obj->object.sphere.radius = 2;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_cylinder(t_object *obj)
{
	srand(time(NULL));
	obj->type = o_cylinder;
	obj->object.cylinder.axis = (cl_float3){0, 1, 0};
	obj->object.cylinder.center = (cl_float3){rand() % 5, rand() % 3, rand() % 10};
	obj->object.cylinder.length = rand() % 4;
	obj->object.cylinder.radius = 2;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_cone(t_object *obj)
{
	srand(time(NULL));
	obj->type = o_cone;
	obj->object.cone.axis = (cl_float3){0, 1, 0};
	obj->object.cone.center = (cl_float3){rand() % 5, rand() % 3, rand() % 10};
	obj->object.cone.length = 2;
	obj->object.cone.tan = 0.25;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_plane(t_object *obj)
{
	srand(time(NULL));
	obj->type = o_plane;
	obj->object.plane.axis = (cl_float3){rand() % 5, rand() % 3, rand() % 10};
	obj->object.plane.dist = 30;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0, (float)(rand() % 255) / 255.0};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		copy_obj(SDL_Event event, t_object *obj, t_object *scene_obj, int count_objects)
{
	int			i;

	i = -1;
	while (++i < count_objects)
	{
		obj[i] = scene_obj[i];
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_KP_0)
		new_sphere(&obj[i]);
	else if (event.key.keysym.scancode == SDL_SCANCODE_KP_1)
		new_cylinder(&obj[i]);
	else if (event.key.keysym.scancode == SDL_SCANCODE_KP_2)
		new_cone(&obj[i]);
	else if (event.key.keysym.scancode == SDL_SCANCODE_KP_3)
		new_plane(&obj[i]);
}

int				realloc_objects(SDL_Event event, t_rt *rt)
{
	int			count_objects;
	t_object	*object;

	count_objects = rt->scene->count_objects;
	rt->scene->count_objects += 1;
	init_objects(&object, rt->scene->count_objects);
	copy_obj(event, object, rt->scene->object, count_objects);
	ft_memdel((void **)&rt->scene->object);
	rt->scene->object = object;
	return (0);
}


static void		add_obj(SDL_Event event, t_rt *rt)
{
	cl_int		ret;

	ret = 0;
	realloc_objects(event, rt);
	clReleaseMemObject(rt->opencl->memobjs[2]);
	if ((rt->opencl->memobjs[2] = clCreateBuffer(rt->opencl->context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_object) * rt->scene->count_objects, rt->scene->object, &ret))
		&& ret != 0)
		ft_error("clCreateBuffer");
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
			add_obj(rt->sdl->event, rt);
		move(rt->sdl->event, rt->sdl, &(rt->scene->cam));
		rotation(rt->sdl->event, rt->sdl, &(rt->scene->cam));
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			save_image(rt->sdl);
		return (1);
	}
	return (0);
}
