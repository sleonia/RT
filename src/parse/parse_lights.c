/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:50:31 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 03:36:18 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			set_default_value(int i, t_scene *scene, char *sounds[])
{
	scene->light[i].intensity = 0;
	scene->light[i].pos = (cl_float3){0, 0, 0};
	show_error(E_LIGHT, sounds);
}

static bool			parse_light_json2(int i, t_key_value *light_obj,
									t_scene *scene)
{
	bool			error;
	t_array			*pos;
	double			value;

	error = false;
	if (get_double(light_obj, "intensity", &value) != 0)
	{
		scene->light[i].intensity = 0;
		error = true;
	}
	else
		scene->light[i].intensity = (float)value;
	if (get_array(light_obj, "position", &pos) != 0)
	{
		scene->light[i].pos = (cl_float3){0, 0, 0};
		error = true;
	}
	else
		parse_array_of_float(pos, &scene->light[i].pos);
	return (error);
}

void				parse_light_json(t_key_value *json,
									t_scene *scene, char *sounds[])
{
	int				i;
	bool			error;
	t_array			*light_array;
	t_key_value		*light_obj;

	i = -1;
	if (get_array(json, "light", &light_array) != 0)
	{
		init_light(&scene->light, 1);
		set_default_value(0, scene, sounds);
		return ;
	}
	init_light(&scene->light, light_array->length);
	while (++i < light_array->length)
	{
		if (getf_object_array(light_array, i, &light_obj) != 0)
		{
			set_default_value(i, scene, sounds);
			return ;
		}
		error = parse_light_json2(i, light_obj, scene);
		if (error)
			show_error(E_LIGHT, sounds);
	}
	scene->count_lights = light_array->length;
}
