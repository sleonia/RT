/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:44:26 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 13:06:44 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static void		new_elem(t_object *obj)
// {
// 	obj->type = o_sphere;
// 	obj->object.sphere.center = (cl_float3){1.0, -3.0, 10.0};
// 	obj->object.sphere.radius = 2;
// 	obj->material.color = (cl_float3){255, 0, 0};
// 	obj->material.ambient = 1.0;
// 	obj->material.diffuse = 0.4;
// 	obj->material.specular = 50;
// 	obj->material.reflection = 0;
// 	obj->material.refraction = 0;
// 	obj->material.texture_id = -1;
// }

// static void		copy_obj(t_object *obj, t_object *scene_obj, int count_objects)
// {
// 	int			i;

// 	i = -1;
// 	while (++i < count_objects)
// 	{
// 		obj[i] = scene_obj[i];
// 		ft_memdel((void **)(&scene_obj[i]);
// 	}
// 	// ft_memdel((void **)(&scene_obj[i]);
// 	new_elem(obj[i]);
// }

// int				realloc_objects(t_rt *rt)
// {
// 	int			count_objects;
// 	t_object	*object;

// 	count_objects = rt->scene->count_objects;
// 	rt->scene->count_objects += 1;
// 	init_objects(&object, rt->scene->count_objects);
// 	copy_obj(object, rt->scene->object)
// 	rt->scene->object = object;
// 	// ft_memdel((void **)(rt->scene->);
// 	return (0);
// }
