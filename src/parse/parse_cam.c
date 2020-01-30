/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:46:46 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 16:00:22 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_cam_json(t_key_value *json, t_scene *scene)
{
	double			phi;
	double			tetta;
	t_key_value		*cam_obj;
	t_array			*array;

	if (get_node(json, "camera", &cam_obj) != 0)
		ft_error("get_node: camera");
	if (get_array(cam_obj, "postition", &array) != 0)
		ft_error("get_array: postition");
	if ((get_double(cam_obj, "phi", &phi)) != 0)
		ft_error("get_double: phi");
	if ((get_double(cam_obj, "tetta", &tetta)) != 0)
		ft_error("get_double: tetta");
	scene->cam.pos = **(cl_float3 **)(array->value);
	scene->cam.phi = (float)phi;
	scene->cam.tetta = (float)tetta;
}
