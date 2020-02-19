/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:16:18 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 15:19:16 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			new_torus(t_object *obj)
{
	obj->type = o_torus;
	obj->object.parab.axis = (cl_float3){{(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5,
										(float)(rand() % 14) + 0.5}};
	cl_normalize(&obj->object.torus.axis);
	obj->object.torus.center = (cl_float3){{rand() % 5,
										rand() % 5,
										rand() % 5}};
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
