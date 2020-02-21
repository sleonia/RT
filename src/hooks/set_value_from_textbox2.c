/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_from_textbox2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:59:33 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 13:00:04 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			def(t_scene *scene, t_textbox *textbox[])
{
	scene->cam.phi = check_phi(atof(textbox[Phi]->text));
	scene->cam.tetta = check_tetta(atof(textbox[Tetta]->text));
	scene->skybox_id = check_skybox(atof(textbox[Id]->text),
									scene->texture_cnt);
	scene->ambient = check_ambient(atof(textbox[Skybox_ambient]->text));
	scene->fsaa = check_fsaa(atof(textbox[Fsaa]->text));
}

void			sphere(t_object **select_obj, t_textbox *textbox[])
{
	cl_float3	tmp;

	tmp = *string_to_float_array(textbox[Sphere_center]->text);
	check_float_array(CENTER_FLAG, &tmp);
	(*select_obj)->object.sphere.center = tmp;
	(*select_obj)->object.sphere.radius =
		check_radius(atof(textbox[Sphere_rad]->text));
}

void			cylinder(t_object **select_obj, t_textbox *textbox[])
{
	cl_float3	tmp;

	tmp = *string_to_float_array(textbox[Cylinder_axis]->text);
	check_float_array(AXIS_FLAG, &tmp);
	cl_normalize(&tmp);
	(*select_obj)->object.cylinder.axis = tmp;
	tmp = *string_to_float_array(textbox[Cylinder_center]->text);
	check_float_array(CENTER_FLAG, &tmp);
	(*select_obj)->object.cylinder.center = tmp;
	(*select_obj)->object.cylinder.length =
		check_length(atof(textbox[Cylinder_len]->text));
	(*select_obj)->object.cylinder.radius =
		check_radius(atof(textbox[Cylinder_rad]->text));
}

void			cone(t_object **select_obj, t_textbox *textbox[])
{
	cl_float3	tmp;

	tmp = *string_to_float_array(textbox[Cone_axis]->text);
	check_float_array(AXIS_FLAG, &tmp);
	cl_normalize(&tmp);
	(*select_obj)->object.cone.axis = tmp;
	tmp = *string_to_float_array(textbox[Cone_center]->text);
	check_float_array(CENTER_FLAG, &tmp);
	(*select_obj)->object.cone.center = tmp;
	(*select_obj)->object.cone.length =
		check_length(atof(textbox[Cone_len]->text));
	(*select_obj)->object.cone.tan = check_tan(atof(textbox[Cone_tan]->text));
}

void			plane(t_object **select_obj, t_textbox *textbox[])
{
	cl_float3	tmp;

	tmp = *string_to_float_array(textbox[Plane_axis]->text);
	check_float_array(AXIS_FLAG, &tmp);
	cl_normalize(&tmp);
	(*select_obj)->object.plane.axis = tmp;
	(*select_obj)->object.plane.dist =
		check_dist(atof(textbox[Plane_tan]->text));
}
