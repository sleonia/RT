/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:46:46 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 03:45:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			set_default_value(t_scene *scene, char *sounds[])
{
	scene->cam.pos = (cl_float3){0, 0, 0};
	scene->cam.phi = 1.570796;
	scene->cam.tetta = 1.570796;
	show_error(E_CAM, sounds);
}

void				parse_cam_json2(t_key_value *cam_obj, t_scene *scene,
								bool *error, char *sounds[])
{
	double			phi;
	double			tetta;

	if ((get_double(cam_obj, "phi", &phi)) != 0)
	{
		*error = true;
		scene->cam.phi = 1.570796;
	}
	else
		scene->cam.phi = (float)phi * M_PI / 180;
	if ((get_double(cam_obj, "tetta", &tetta)) != 0)
	{
		*error = true;
		scene->cam.tetta = 1.570796;
	}
	else
		scene->cam.tetta = (float)tetta * M_PI / 180;
}

void				parse_array_of_float(t_array *array, cl_float3 *pos)
{
	size_t			i;
	double			container;

	i = -1;
	while (++i < array->length)
	{
		if (getf_double_array(array, i, &container) != 0)
			pos->s[i] = 0.f;
		else
			pos->s[i] = (cl_float)container;
	}
}

void				parse_cam_json(t_key_value *json, t_scene *scene,
								char *sounds[])
{
	bool			error;
	t_key_value		*cam_obj;
	t_array			*array;

	error = false;
	if (get_node(json, "camera", &cam_obj) != 0)
	{
		set_default_value(scene, sounds);
		return ;
	}
	if (get_array(cam_obj, "position", &array) != 0)
	{
		scene->cam.pos = (cl_float3){0, 0, 0};
		error = true;
	}
	else
		parse_array_of_float(array, &scene->cam.pos);
	parse_cam_json2(cam_obj, scene, &error, sounds);
	if (error)
		show_error(E_CAM, sounds);
}
