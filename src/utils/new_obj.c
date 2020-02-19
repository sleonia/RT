/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:15:33 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 15:18:50 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			new_sphere(t_object *obj)
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

void			new_cylinder(t_object *obj)
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

void			new_cone(t_object *obj)
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

void			new_plane(t_object *obj)
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

void			new_parab(t_object *obj)
{
	obj->type = o_parab;
	obj->object.parab.axis = (cl_float3){{(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5}};
	cl_normalize(&obj->object.parab.axis);
	obj->object.parab.center = (cl_float3){{rand() % 5,
											rand() % 5,
											rand() % 5}};
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
