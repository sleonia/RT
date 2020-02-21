/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_set_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:35:12 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 04:52:21 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			set_value_in_def_textbox(t_scene *scene,
									t_gui *gui)
{
	sprintf(gui->textbox[Phi]->text, "%3.3f", scene->cam.phi);
	sprintf(gui->textbox[Tetta]->text, "%3.3f", scene->cam.tetta);	
	sprintf(gui->textbox[Id]->text, "%1d", scene->skybox_id);
	sprintf(gui->textbox[Skybox_ambient]->text, "%3.3f", scene->ambient);
	sprintf(gui->textbox[Fsaa]->text, "%1d", scene->fsaa);
	sprintf(gui->textbox[New_obj]->text, "%d", 0);
}

void			set_value_in_material_textbox(t_object **hi_lited_object,
									t_gui *gui)
{
	char	*tmp;

	tmp = color_to_string((*hi_lited_object)->material.color);
	gui->textbox[Mtrl_Color]->text = tmp;
	sprintf(gui->textbox[Mtrl_ambient]->text, "%3.3f", (*hi_lited_object)->material.ambient);
	sprintf(gui->textbox[Mtrl_diffuse]->text, "%3.3f", (*hi_lited_object)->material.diffuse);
	sprintf(gui->textbox[Mtrl_specular]->text, "%3.3f", (*hi_lited_object)->material.specular);
	sprintf(gui->textbox[Mtrl_reflection]->text, "%3.3f", (*hi_lited_object)->material.reflection);
	sprintf(gui->textbox[Mtrl_refraction]->text, "%3.3f", (*hi_lited_object)->material.refraction);
	sprintf(gui->textbox[Mtrl_texture_id]->text, "%d", (*hi_lited_object)->material.texture_id);
}

static void		set_value_in_sphere_textbox(t_sphere *sphere,
									t_gui *gui)
{
	char		*tmp;

	tmp = float_array_to_string(sphere->center);
	gui->textbox[Sphere_center]->text = tmp;
	sprintf(gui->textbox[Sphere_rad]->text, "%3.3f", sphere->radius);
}

static void		set_value_in_cylinder_textbox(t_cylinder *cylinder,
									t_gui *gui)
{
	char		*tmp;

	tmp = float_array_to_string(cylinder->axis);
	gui->textbox[Cylinder_axis]->text = tmp;
	tmp = float_array_to_string(cylinder->center);
	gui->textbox[Cylinder_center]->text = tmp;
	sprintf(gui->textbox[Cylinder_len]->text, "%3.3f", cylinder->length);
	sprintf(gui->textbox[Cylinder_rad]->text, "%3.3f", cylinder->radius);
}

static void		set_value_in_cone_textbox(t_cone *cone,
									t_gui *gui)
{
	char		*tmp;

	tmp = float_array_to_string(cone->axis);
	gui->textbox[Cone_axis]->text = tmp;
	tmp = float_array_to_string(cone->center);
	gui->textbox[Cone_center]->text = tmp;
	sprintf(gui->textbox[Cone_len]->text, "%3.3f", cone->length);
	sprintf(gui->textbox[Cone_tan]->text, "%3.3f", cone->tan);
}

static void		set_value_in_plane_textbox(t_plane *plane,
									t_gui *gui)
{
	char		*tmp;

	tmp = float_array_to_string(plane->axis);
	gui->textbox[Plane_axis]->text = tmp;
	sprintf(gui->textbox[Plane_tan]->text, "%3.3f", plane->dist);
}

static void		set_value_in_parab_textbox(t_parab *parab,
									t_gui *gui)
{
	char		*tmp;

	tmp = float_array_to_string(parab->axis);
	gui->textbox[Parab_axis]->text = tmp;
	tmp = float_array_to_string(parab->center);
	gui->textbox[Parab_center]->text = tmp;
	sprintf(gui->textbox[Parab_dist]->text, "%3.3f", parab->k);
	sprintf(gui->textbox[Parab_len]->text, "%3.3f", parab->length);
}

static void		set_value_in_torus_textbox(t_torus *torus,
									t_gui *gui)
{
	char		*tmp;

	tmp = float_array_to_string(torus->axis);
	gui->textbox[Torus_axis]->text = tmp;
	tmp = float_array_to_string(torus->center);
	gui->textbox[Torus_center]->text = tmp;
	sprintf(gui->textbox[Torus_bigr]->text, "%3.3f", torus->bigr);
	sprintf(gui->textbox[Torus_r]->text, "%3.3f", torus->r);
}

void			set_textbox_value(t_scene *scene, t_object **hi_lited_object, t_gui *gui)
{
	if (!*hi_lited_object)
		set_value_in_def_textbox(scene, gui);
	else if ((*hi_lited_object)->type == o_sphere)
		set_value_in_sphere_textbox(&(*hi_lited_object)->object.sphere, gui);
	else if ((*hi_lited_object)->type == o_cylinder)
		set_value_in_cylinder_textbox(&(*hi_lited_object)->object.cylinder, gui);
	else if ((*hi_lited_object)->type == o_cone)
		set_value_in_cone_textbox(&(*hi_lited_object)->object.cone, gui);
	else if ((*hi_lited_object)->type == o_plane)
		set_value_in_plane_textbox(&(*hi_lited_object)->object.plane, gui);
	else if ((*hi_lited_object)->type == o_parab)
		set_value_in_parab_textbox(&(*hi_lited_object)->object.parab, gui);
	else if ((*hi_lited_object)->type == o_torus)
		set_value_in_torus_textbox(&(*hi_lited_object)->object.torus, gui);
	if (*hi_lited_object)
		set_value_in_material_textbox(hi_lited_object, gui);
}
