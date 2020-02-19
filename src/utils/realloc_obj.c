/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:44:26 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 14:33:30 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		new_sphere(t_object *obj)
{
	obj->type = o_sphere;
	obj->object.sphere.center = (cl_float3){{rand() % 5,
										rand() % 3,
										rand() % 10, 0.f}};
	obj->object.sphere.radius = rand() % 7 + 2;
	obj->material.color = (cl_float3){{(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0}};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_cylinder(t_object *obj)
{
	obj->type = o_cylinder;
	obj->object.cylinder.axis = (cl_float3){{0, 1, 0}};
	cl_normalize(&obj->object.cylinder.axis);
	obj->object.cylinder.center = (cl_float3){{rand() % 5,
											rand() % 3,
											rand() % 10}};
	obj->object.cylinder.length = rand() % 50 + 10;
	obj->object.cylinder.radius = (rand() % 20) / 10.f + 1;
	obj->material.color = (cl_float3){{(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0}};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_cone(t_object *obj)
{
	obj->type = o_cone;
	obj->object.cone.axis = (cl_float3){{(float)(rand() % 14) + 0.5,
									(float)(rand() % 14) + 0.5,
									(float)(rand() % 14) + 0.5}};
	cl_normalize(&obj->object.cone.axis);
	obj->object.cone.center = (cl_float3){{rand() % 5,
										rand() % 3,
										rand() % 10}};
	obj->object.cone.length = rand() % 50 + 10;
	obj->object.cone.tan = 0.25;
	obj->material.color = (cl_float3){{(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0}};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_plane(t_object *obj)
{
	obj->type = o_plane;
	obj->object.plane.axis = (cl_float3){{rand() % 5, rand() % 3, rand() % 10}};
	obj->object.plane.dist = 30;
	obj->material.color = (cl_float3){{(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0}};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_parab(t_object *obj)
{
	obj->type = o_parab;
	obj->object.parab.axis = (cl_float3){{(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5}};
	cl_normalize(&obj->object.parab.axis);
	obj->object.parab.center = (cl_float3){{rand() % 5, rand() % 5, rand() % 5}};
	obj->object.parab.k = 0.6;
	obj->object.parab.length = 30;
	obj->material.color = (cl_float3){{(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0}};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

static void		new_torus(t_object *obj)
{
	obj->type = o_torus;
	obj->object.parab.axis = (cl_float3){{(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5}};
	cl_normalize(&obj->object.torus.axis);
	obj->object.torus.center = (cl_float3){{rand() % 5, rand() % 5, rand() % 5}};
	obj->object.torus.bigr = (float)(rand() % 5) + 10;
	obj->object.torus.r = (float)(rand() % 2) + 3;
	obj->material.color = (cl_float3){{(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0,
									(float)(rand() % 255) / 255.0}};
	obj->material.ambient = 1.0;
	obj->material.diffuse = 0.4;
	obj->material.specular = 50;
	obj->material.reflection = 0;
	obj->material.refraction = 0;
	obj->material.texture_id = -1;
}

int				realloc_obj(SDL_Scancode scancode, t_scene *scene)
{
	int			i;
	int			count_objects;
	t_object	*object;

	i = -1;
	count_objects = scene->count_objects;
	scene->count_objects += 1;
	init_objects(&object, scene->count_objects);
	while (++i < count_objects)
		object[i] = scene->object[i];
	if (scancode == SDL_SCANCODE_KP_1)
		new_sphere(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_2)
		new_cylinder(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_3)
		new_cone(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_4)
		new_plane(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_5)
		new_parab(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_6)
		new_torus(&object[i]);
	ft_memdel((void **)&scene->object);
	scene->object = object;
	return (0);
}
