/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_set_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:35:12 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 16:57:14 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			set_value_in_def_textbox(t_scene *scene,
									t_textbox *textbox[])
{
	sprintf(textbox[Phi]->text, "%3.3f", scene->cam.phi);
	sprintf(textbox[Tetta]->text, "%3.3f", scene->cam.tetta);
	sprintf(textbox[Id]->text, "%1d", scene->skybox_id);
	sprintf(textbox[Skybox_ambient]->text, "%3.3f", scene->ambient);
	sprintf(textbox[Fsaa]->text, "%1d", scene->fsaa);
	sprintf(textbox[New_obj]->text, "%d", 0);
}

void			set_value_in_material_textbox(t_material *material,
											t_textbox *textbox[])
{
	char	*tmp;

	ft_strdel(&textbox[Mtrl_Color]->text);
	tmp = color_to_string(material->color);
	textbox[Mtrl_Color]->text = tmp;
	sprintf(textbox[Mtrl_ambient]->text, "%3.3f", material->ambient);
	sprintf(textbox[Mtrl_diffuse]->text, "%3.3f", material->diffuse);
	sprintf(textbox[Mtrl_specular]->text, "%3.3f", material->specular);
	sprintf(textbox[Mtrl_reflection]->text, "%3.3f", material->reflection);
	sprintf(textbox[Mtrl_refraction]->text, "%3.3f", material->refraction);
	sprintf(textbox[Mtrl_texture_id]->text, "%d", material->texture_id);
}

static void		set_value_in_sphere_textbox(t_sphere *sphere,
									t_textbox *textbox[])
{
	char		*tmp;

	ft_strdel(&textbox[Sphere_center]->text);
	tmp = float_array_to_string(sphere->center);
	textbox[Sphere_center]->text = tmp;
	sprintf(textbox[Sphere_rad]->text, "%3.3f", sphere->radius);
}

void			set_textbox_value(t_scene *scene,
								t_object **select_obj,
								t_gui *gui)
{
	if (!*select_obj)
		set_value_in_def_textbox(scene, gui->textbox);
	else if ((*select_obj)->type == o_sphere)
		set_value_in_sphere_textbox(&(*select_obj)->object.sphere,
									gui->textbox);
	else if ((*select_obj)->type == o_cylinder)
		set_value_in_cylinder_textbox(&(*select_obj)->object.cylinder,
									gui->textbox);
	else if ((*select_obj)->type == o_cone)
		set_value_in_cone_textbox(&(*select_obj)->object.cone, gui->textbox);
	else if ((*select_obj)->type == o_plane)
		set_value_in_plane_textbox(&(*select_obj)->object.plane, gui->textbox);
	else if ((*select_obj)->type == o_parab)
		set_value_in_parab_textbox(&(*select_obj)->object.parab, gui->textbox);
	else if ((*select_obj)->type == o_torus)
		set_value_in_torus_textbox(&(*select_obj)->object.torus, gui->textbox);
	if (*select_obj)
		set_value_in_material_textbox(&(*select_obj)->material, gui->textbox);
}
