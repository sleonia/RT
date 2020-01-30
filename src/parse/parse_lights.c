/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:50:31 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 22:51:56 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			show_error_in_light(t_rt *rt)
{
	system("osascript -e \'display notification\" \
		Used default value!\" with title \"Error light!\"\'");
	playSound(rt->sdl->sounds[0], 100);
	SDL_Delay(1500);
}

static void			set_default_value(int i, t_scene *scene, t_rt *rt)
{
	scene->light[i].intensity = 0;
	scene->light[i].pos = (cl_float3){0, 0, 0};
	show_error_in_light(rt);
}

static bool			parse_light_json2(int i, t_key_value *light_obj,
									t_scene *scene)
{
	bool			error;
	t_array			*pos;
	double			value;

	error = false;
	if (get_double(light_obj, "intensity", &value))
	{
		scene->light[i].intensity = 0;
		*error = true;
	}
	else
		scene->light[i].intensity = value;
	if (get_array(light_obj, "position", &pos))
	{
		scene->light[i].pos = (cl_float3){0, 0, 0};
		*error = true;
	}
	else
		scene->light[i].pos = **(cl_float3**)(pos->value);
	return (error);
}

void				parse_light_json(t_key_value *json,
									t_scene *scene, t_rt *rt)
{
	int				i;
	bool			error;
	t_array			*light_array;
	t_key_value		*light_obj;

	i = -1;
	if (get_array(json, "light", &light_array) != 0)
	{
		init_light(&scene->light, 1);
		set_default_value(0, scene, rt);
		return ;
	}
	init_light(&scene->light, light_array->length);
	while (++i < light_array->length)
	{
		if (getf_object_array(light_array, i, &light_obj) != 0)
		{
			set_default_value(i, scene, rt);
			return ;
		}
		error = parse_light_json2(i, light_obj, scene);
	}
	if (error)
		show_error_in_light(rt);
	scene->count_lights = light_array->length;
}
