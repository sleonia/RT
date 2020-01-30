/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:50:31 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 16:55:14 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_light_json(t_key_value *json, t_scene *scene)
{
	int				i;
	double			value;
	t_array			*light_array;
	t_key_value		*light_obj;
	t_array			*pos;

	i = -1;
	if (get_array(json, "light", &light_array) != 0)
		ft_error("Error get_array: light");
	init_light(&scene->light, light_array->length);
	while (++i < light_array->length)
	{
		if (getf_object_array(light_array, i, &light_obj) != 0)
			ft_error("Error getf_object_array: light_obj");
		if (get_double(light_obj, "intensity", &value))
			ft_error("Error get_double: intensity");
		scene->light[i].intensity = value;
		if (get_array(light_obj, "position", &pos))
			ft_error("Error get_array: position");
		scene->light[i].pos = **(cl_float3 **)(pos->value);
	}
	scene->count_lights = light_array->length;
}
