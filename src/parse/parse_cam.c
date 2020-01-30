/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:46:46 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 22:25:04 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			show_error_in_cam(t_rt *rt)
{
	system("osascript -e \'display notification\" \
		Used default value!\" with title \"Error camera!\"\'");
	if (ft_len_arr(rt->sdl->sounds) >= 1)
		playSound(rt->sdl->sounds[1], 100);
	else
		playSound(rt->sdl->sounds[0], 100);	
	SDL_Delay(1500);
}

static void			set_default_value(t_scene *scene, t_rt *rt)
{
	scene->cam.pos = (cl_float3 ){0, 0, 0};
	scene->cam.phi = 0;
	scene->cam.tetta = 0;
	show_error_in_cam(rt);
}

void				parse_cam_json2(t_key_value *cam_obj, t_scene *scene,
								bool *error, t_rt *rt)
{
	double			phi;
	double			tetta;

	if ((get_double(cam_obj, "phi", &phi)) != 0)
	{
		*error = true;
		scene->cam.phi = 0;
	}
	else		
		scene->cam.phi = (float)phi;
	if ((get_double(cam_obj, "tetta", &tetta)) != 0)
	{
		*error = true;
		scene->cam.tetta = 0;
	}
	else
		scene->cam.tetta = (float)tetta;
}

void				parse_cam_json(t_key_value *json, t_scene *scene, t_rt *rt)
{
	bool			error;
	t_key_value		*cam_obj;
	t_array			*array;

	error = false;
	if (get_node(json, "camera", &cam_obj) != 0)
	{
		set_default_value(scene, rt);
		return ;
	}
	if (get_array(cam_obj, "postition", &array) != 0)
	{
		scene->cam.pos = (cl_float3 ){0, 0, 0};
		error = true;
	}
	else
		scene->cam.pos = **(cl_float3 **)(array->value);
	parse_cam_json2(cam_obj, scene, &error, rt);
	if (error)
		show_error_in_cam(rt);
}
