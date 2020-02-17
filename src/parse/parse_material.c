/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:25:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 08:28:00 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			set_default_value(t_object *object, char *sounds[])
{
	object->material.color = (cl_float3){{1.f, 1.f, 1.f, 0.f}};
	object->material.ambient = 1.0;
	object->material.diffuse = 0.4;
	object->material.specular = 50;
	object->material.reflection = 0;
	object->material.refraction = 0;
	object->material.texture_id = -1;
	show_error(E_MAT, sounds);
}

static void			parse_material_json1(t_key_value *material,
									t_object *object)
{
	double			d_value;

	if (get_double(material, "ambient", &d_value) != 0)
		object->material.ambient = 0;
	else
		object->material.ambient = (float)d_value;
	if (get_double(material, "diffuse", &d_value) != 0)
		object->material.diffuse = 0;
	else
		object->material.diffuse = (float)d_value;
	if (get_double(material, "specular", &d_value) != 0)
		object->material.specular = 0;
	else
		object->material.specular = (float)d_value;
	if (get_double(material, "reflection", &d_value))
		object->material.reflection = 0;
	else
		object->material.reflection = (float)d_value;
	if (get_double(material, "refraction", &d_value))
		object->material.refraction = 0;
	else
		object->material.refraction = (float)d_value;
}

void				parse_material_json(t_key_value *obj, t_object *object,
									int texture_cnt, char *sounds[])
{
	t_array			*array;
	t_key_value		*material;
	int				value;

	if (get_node(obj, "material", &material) != 0)
	{
		set_default_value(object, sounds);
		return ;
	}
	if (get_array(material, "color", &array) != 0)
		object->material.color = (cl_float3){{1.f, 1.f, 1.f, 0.f}};
	else
	{
		parse_array_of_float(array, &object->material.color);
		object->material.color =
			cl_mult_n(object->material.color, 1.f / 255.f);
	}
	parse_material_json1(material, object);
	if (get_int(material, "texture_id", &value)
		|| (value >= texture_cnt))
		object->material.texture_id = -1;
	else
		object->material.texture_id = value;
}
