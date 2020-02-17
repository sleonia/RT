/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:51:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 08:28:25 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			check_type1(char *type, t_object *scene_obj,
							t_key_value *obj)
{
	union u_objects	object;

	if (ft_strcmp(type, "cone") == 0)
	{
		scene_obj->type = o_cone;
		parse_cone_json(obj, &object.cone);
		scene_obj->object.cone = object.cone;
	}
	else if (ft_strcmp(type, "plane") == 0)
	{
		scene_obj->type = o_plane;
		parse_plane_json(obj, &object.plane);
		scene_obj->object.plane = object.plane;
	}
	else if (ft_strcmp(type, "parab") == 0)
	{
		scene_obj->type = o_parab;
		parse_parab_json(obj, &object.parab);
		scene_obj->object.parab = object.parab;
	}
}

static void			check_type(char *type, t_object *scene_obj,
							t_key_value *obj)
{
	union u_objects	object;

	if (ft_strcmp(type, "sphere") == 0)
	{
		scene_obj->type = o_sphere;
		parse_sphere_json(obj, &object.sphere);
		scene_obj->object.sphere = object.sphere;
	}
	else if (ft_strcmp(type, "cylinder") == 0)
	{
		scene_obj->type = o_cylinder;
		parse_cylinder_json(obj, &object.cylinder);
		scene_obj->object.cylinder = object.cylinder;
	}
	else if (ft_strcmp(type, "torus") == 0)
	{
		scene_obj->type = o_torus;
		parse_torus_json(obj, &object.torus);
		scene_obj->object.torus = object.torus;
	}
	check_type1(type, scene_obj, obj);
}

void				parse_objects_json(t_key_value *json, t_scene *scene,
									char *sounds[])
{
	int				i;
	char			*str_value;
	t_array			*json_obj_array;
	t_key_value		*json_obj;

	i = -1;
	if (get_array(json, "figure", &json_obj_array) != 0)
		ft_error("Error get_array: figure");
	init_objects(&scene->object, json_obj_array->length);
	while (++i < (int)json_obj_array->length)
	{
		if (getf_object_array(json_obj_array, i, &json_obj) != 0)
			ft_error("Error getf_object_array: obj");
		if (get_str(json_obj, "type", &str_value) != 0)
			ft_error("\033[31mError figures type\033[0m");
		check_type(str_value, &(scene->object[i]), json_obj);
		parse_material_json(json_obj, &(scene->object[i]),
							scene->texture_cnt, sounds);
		ft_strdel(&str_value);
	}
	scene->count_objects = json_obj_array->length;
}
