/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_from_textbox.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 05:34:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 18:17:52 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parab(t_object **select_obj, t_textbox *textbox[])
{
	cl_float3	tmp;

	tmp = *string_to_float_array(textbox[Parab_axis]->text);
	check_float_array(AXIS_FLAG, &tmp);
	cl_normalize(&tmp);
	(*select_obj)->object.parab.axis = tmp;
	tmp = *string_to_float_array(textbox[Parab_center]->text);
	check_float_array(CENTER_FLAG, &tmp);
	(*select_obj)->object.parab.center = tmp;
	(*select_obj)->object.parab.length =
		check_length(atof(textbox[Parab_len]->text));
	(*select_obj)->object.parab.k = (atof(textbox[Parab_dist]->text));
}

void			torus(t_object **select_obj, t_textbox *textbox[])
{
	cl_float3	tmp;

	tmp = *string_to_float_array(textbox[Torus_axis]->text);
	check_float_array(AXIS_FLAG, &tmp);
	cl_normalize(&tmp);
	(*select_obj)->object.torus.axis = tmp;
	tmp = *string_to_float_array(textbox[Torus_center]->text);
	check_float_array(CENTER_FLAG, &tmp);
	(*select_obj)->object.torus.center = tmp;
	(*select_obj)->object.torus.bigr =
		check_length(atof(textbox[Torus_bigr]->text));
	(*select_obj)->object.torus.r = (atof(textbox[Torus_r]->text));
}

void			material(int texture_cnt,
						t_material *material,
						t_textbox *textbox[])
{
	double		res;
	cl_float3	tmp;

	tmp = *string_to_color(textbox[Mtrl_Color]->text);
	material->color = tmp;
	material->ambient = check_ambient(atof(textbox[Mtrl_ambient]->text));
	res = atof(textbox[Mtrl_diffuse]->text);
	material->diffuse = (res > 0.1 && res <= 1.0) ? res : 0.4;
	res = atof(textbox[Mtrl_specular]->text);
	material->specular = (res > 0.0 && res <= 100.0) ? res : 50.0;
	res = atof(textbox[Mtrl_reflection]->text);
	material->reflection = (res > 0.0 && res <= 1.0) ? res : 0.0;
	res = atof(textbox[Mtrl_refraction]->text);
	material->refraction = (res >= 1.0 && res <= 1.3) ? res : 0.0;
	res = atof(textbox[Mtrl_texture_id]->text);
	material->texture_id = (res > texture_cnt - 1 ? -1 : res);
}

void			set_value_from_textbox(t_object **select_obj,
									t_scene *scene,
									t_textbox *textbox[],
									t_cl *cl)
{
	int			obj;

	if (!(*select_obj))
		def(scene, textbox);
	else if ((*select_obj)->type == o_sphere)
		sphere(select_obj, textbox);
	else if ((*select_obj)->type == o_cylinder)
		cylinder(select_obj, textbox);
	else if ((*select_obj)->type == o_cone)
		cone(select_obj, textbox);
	else if ((*select_obj)->type == o_plane)
		plane(select_obj, textbox);
	else if ((*select_obj)->type == o_parab)
		parab(select_obj, textbox);
	else if ((*select_obj)->type == o_torus)
		torus(select_obj, textbox);
	if (*select_obj)
		material(scene->texture_cnt, &(*select_obj)->material, textbox);
	if ((obj = (88 + ft_atoi(textbox[New_obj]->text)) > 0))
		add_obj(obj, scene, cl);
}
