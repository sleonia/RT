/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_from_textbox.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 05:34:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 06:40:51 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_value_from_textbox(t_object **hi_lited_object,
								t_scene *scene,
								t_textbox *textbox[],
								t_cl *cl)
{
	int			obj;
	cl_float3	tmp;

	if (!(*hi_lited_object))
	{
		scene->cam.phi = check_phi(atof(textbox[Phi]->text));
		scene->cam.tetta = check_tetta(atof(textbox[Tetta]->text));
		scene->skybox_id = check_skybox(atof(textbox[Id]->text),
										scene->texture_cnt);
		scene->ambient = check_ambient(atof(textbox[Skybox_ambient]->text));
		scene->fsaa = check_fsaa(atof(textbox[Fsaa]->text));
	}
	else if ((*hi_lited_object)->type == o_sphere)
	{
		tmp = *string_to_float_array(textbox[Sphere_center]->text);
		check_float_array(CENTER_FLAG, &tmp);
		(*hi_lited_object)->object.sphere.center = tmp;
		(*hi_lited_object)->object.sphere.radius = check_radius(atof(textbox[Sphere_rad]->text));
	}
	else if ((*hi_lited_object)->type == o_cylinder)
	{
		tmp = *string_to_float_array(textbox[Cylinder_axis]->text);
		check_float_array(AXIS_FLAG, &tmp);
		cl_normalize(&tmp);
		(*hi_lited_object)->object.cylinder.axis = tmp;
		tmp = *string_to_float_array(textbox[Cylinder_center]->text);
		check_float_array(CENTER_FLAG, &tmp);
		(*hi_lited_object)->object.cylinder.center = tmp;
		(*hi_lited_object)->object.cylinder.length = check_length(atof(textbox[Cylinder_len]->text));
		(*hi_lited_object)->object.cylinder.radius = check_radius(atof(textbox[Cylinder_rad]->text));
	}
	else if ((*hi_lited_object)->type == o_cone)
	{
		tmp = *string_to_float_array(textbox[Cone_axis]->text);
		check_float_array(AXIS_FLAG, &tmp);
		cl_normalize(&tmp);
		(*hi_lited_object)->object.cone.axis = tmp;
		tmp = *string_to_float_array(textbox[Cone_center]->text);
		check_float_array(CENTER_FLAG, &tmp);
		(*hi_lited_object)->object.cone.center = tmp;
		(*hi_lited_object)->object.cone.length = check_length(atof(textbox[Cone_len]->text));
		(*hi_lited_object)->object.cone.tan = check_tan(atof(textbox[Cone_tan]->text));
	}
	else if ((*hi_lited_object)->type == o_plane)
	{
		tmp = *string_to_float_array(textbox[Plane_axis]->text);
		check_float_array(AXIS_FLAG, &tmp);
		cl_normalize(&tmp);
		(*hi_lited_object)->object.plane.axis = tmp;
		(*hi_lited_object)->object.plane.dist = check_dist(atof(textbox[Plane_tan]->text));
	}
	else if ((*hi_lited_object)->type == o_parab)
	{
		tmp = *string_to_float_array(textbox[Parab_axis]->text);
		check_float_array(AXIS_FLAG, &tmp);
		cl_normalize(&tmp);
		(*hi_lited_object)->object.parab.axis = tmp;
		tmp = *string_to_float_array(textbox[Parab_center]->text);
		check_float_array(CENTER_FLAG, &tmp);
		(*hi_lited_object)->object.parab.center = tmp;
		(*hi_lited_object)->object.parab.length = check_length(atof(textbox[Parab_len]->text));
		(*hi_lited_object)->object.parab.k = (atof(textbox[Parab_dist]->text));
	}
	if (*hi_lited_object)
	{
		tmp = *string_to_color(textbox[Mtrl_Color]->text);
		(*hi_lited_object)->material.color = tmp;
		(*hi_lited_object)->material.ambient = check_ambient(atof(textbox[Mtrl_ambient]->text));
		(*hi_lited_object)->material.diffuse = atof(textbox[Mtrl_diffuse]->text);
		(*hi_lited_object)->material.specular = atof(textbox[Mtrl_specular]->text);
		(*hi_lited_object)->material.reflection = atof(textbox[Mtrl_reflection]->text);
		(*hi_lited_object)->material.refraction = atof(textbox[Mtrl_refraction]->text);
		(*hi_lited_object)->material.texture_id = atof(textbox[Mtrl_texture_id]->text);
	}
	if ((obj = (88 + ft_atoi(textbox[New_obj]->text)) > 0))
		add_obj(obj, scene, cl);
}
