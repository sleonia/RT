/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:44:26 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/05 19:29:16 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		new_sphere(t_object *obj)
{
	srand(time(NULL));
	obj->type = o_sphere;
	obj->object.sphere.center = (cl_float3){rand() % 5,
										rand() % 3,
										rand() % 10};
	obj->object.sphere.radius = 2;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0};
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
	obj->object.cylinder.center = (cl_float3){rand() % 5,
											rand() % 3,
											rand() % 10};
	obj->object.cylinder.length = rand() % 1 + 3;
	obj->object.cylinder.radius = (rand() % 20) / 10.f + 1;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0};
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
	obj->object.cone.center = (cl_float3){rand() % 5,
										rand() % 3,
										rand() % 10};
	obj->object.cone.length = 2;
	obj->object.cone.tan = 0.25;
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0};
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
	obj->material.color = (cl_float3){(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

int				realloc_obj(SDL_Event event, t_rt *rt)
{
	int			i;
	int			count_objects;
	t_object	*object;

	i = -1;
	count_objects = rt->scene->count_objects;
	rt->scene->count_objects += 1;
	init_objects(&object, rt->scene->count_objects);
	while (++i < count_objects)
	{
		object[i] = rt->scene->object[i];
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_KP_0)
		new_sphere(&object[i]);
	else if (event.key.keysym.scancode == SDL_SCANCODE_KP_1)
		new_cylinder(&object[i]);
	else if (event.key.keysym.scancode == SDL_SCANCODE_KP_2)
		new_cone(&object[i]);
	else if (event.key.keysym.scancode == SDL_SCANCODE_KP_3)
		new_plane(&object[i]);
	ft_memdel((void **)&rt->scene->object);
	rt->scene->object = object;
	return (0);
}
