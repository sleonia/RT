/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:51:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/31 00:25:08 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			show_error_in_obj(t_rt *rt)
{
	system("osascript -e \'display notification\" \
		Used default value!\" with title \"Error object!\"\'");
	if (ft_len_arr(rt->sdl->sounds) >= 1)
		playSound(rt->sdl->sounds[1], 100);
	else
		playSound(rt->sdl->sounds[0], 100);
	SDL_Delay(1500);
}

static bool			check_type1(int i, char *type,
							t_scene *scene, t_key_value *obj)
{
	union u_objects	object;

	if (ft_strcmp(type, "cone") == 0)
	{
		scene->object[i].type = o_cone;
		parse_cone_json(obj, &object.cone);
		scene->object[i].object.cone = object.cone;
	}
	else if (ft_strcmp(type, "plane") == 0)
	{
		scene->object[i].type = o_plane;
		parse_plane_json(obj, &object.plane);
		scene->object[i].object.plane = object.plane;
	}
	else
		return (false);
	return (true);
}

static bool			check_type(int i, char *type,
							t_scene *scene, t_key_value *obj)
{
	union u_objects	object;

	if (ft_strcmp(type, "sphere") == 0)
	{
		scene->object[i].type = o_sphere;
		parse_sphere_json(obj, &object.sphere);
		scene->object[i].object.sphere = object.sphere;
	}
	else if (ft_strcmp(type, "cylinder") == 0)
	{
		scene->object[i].type = o_cylinder;
		parse_cylinder_json(obj, &object.cylinder);
		scene->object[i].object.cylinder = object.cylinder;
	}
	else
		return (check_type1(i, type, scene, obj));
	return (true);
}

void				parse_objects_json(t_key_value *json,
									t_scene *scene, t_rt *rt)
{
	int				i;
	char			*str_value;
	t_array			*obj_array;
	t_key_value		*obj;
	union u_objects	object;

	i = -1;
	if (get_array(json, "figure", &obj_array) != 0)
		ft_error("Error get_array: figure");
	init_objects(&scene->object, obj_array->length);
	while (++i < obj_array->length)
	{
		if (getf_object_array(obj_array, i, &obj) != 0)
			ft_error("Error getf_object_array: obj");
		if (get_str(obj, "type", &str_value) != 0)
			str_value = "sphere";
		if (!check_type(i, str_value, scene, obj))
		{
			show_error_in_obj(rt);
			continue ;
		}
		parse_material_json(i, obj, scene, rt);
	}
	printf("%f\n%f\n%f\n%f\n", scene->object[0].material.ambient, scene->object[1].material.ambient, scene->object[2].material.ambient, scene->object[3].material.ambient);
	scene->count_lights = obj_array->length;
}
