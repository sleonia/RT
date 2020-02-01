/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:50:31 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 15:22:34 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			set_default_value(t_light *light, char *sounds[])
{
	light->intensity = 0;
	light->pos = (cl_float3){0, 0, 0};
	show_error(E_LIGHT, sounds);
}

static void			parse_light_json2(t_key_value *light_obj,
									bool *error, t_light *light)
{
	t_array			*pos;
	double			value;

	*error = false;
	if (get_double(light_obj, "intensity", &value) != 0)
	{
		light->intensity = 0;
		*error = true;
	}
	else
		light->intensity = (float)value;
	if (get_array(light_obj, "position", &pos) != 0)
	{
		light->pos = (cl_float3){0, 0, 0};
		*error = true;
	}
	else
		parse_array_of_float(pos, &light->pos);
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
		set_default_value(&(scene->light[0]), sounds);
		return ;
	}
	init_light(&scene->light, light_array->length);
	while (++i < light_array->length)
	{
		if (getf_object_array(light_array, i, &light_obj) != 0)
		{
			set_default_value(&(scene->light[i]), sounds);
			return ;
		}
		parse_light_json2(light_obj, &error, &(scene->light[i]));
		if (error)
			show_error(E_LIGHT, sounds);
	}
	scene->count_lights = light_array->length;
}
