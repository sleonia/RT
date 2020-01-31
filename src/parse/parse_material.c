/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:25:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/31 08:56:19 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			show_error_in_material(t_rt *rt)
{
	system("osascript -e \'display notification\" \
		Used default value!\" with title \"Error object!\"\'");
	if (ft_len_arr(rt->sdl->sounds) >= 1)
		playSound(rt->sdl->sounds[1], 100);
	else
		playSound(rt->sdl->sounds[0], 100);
	SDL_Delay(1500);
}

static void			set_default_value(int i, t_scene *scene, t_rt *rt)
{
	scene->object[i].material.color = (cl_float3){1.f, 1.f, 1.f};
	scene->object[i].material.ambient = 0;
	scene->object[i].material.diffuse = 0;
	scene->object[i].material.specular = 0;
	scene->object[i].material.reflection = 0;
	scene->object[i].material.refraction = 0;
	scene->object[i].material.texture_id = -1;
	show_error_in_material(rt);
}

static void			parse_material_json1(int i, t_key_value *material,
										t_scene *scene)
{
	double			d_value;

	if (get_double(material, "ambient", &d_value) != 0)
		scene->object[i].material.ambient = 0;
	else
		scene->object[i].material.ambient = (float)d_value;
	if (get_double(material, "diffuse", &d_value) != 0)
		scene->object[i].material.diffuse = 0;
	else
		scene->object[i].material.diffuse = (float)d_value;
	if (get_double(material, "specular", &d_value) != 0)
		scene->object[i].material.specular = 0;
	else
		scene->object[i].material.specular = (float)d_value;
	if (get_double(material, "reflection", &d_value))
		scene->object[i].material.reflection = 0;
	else
		scene->object[i].material.reflection = (float)d_value;
	if (get_double(material, "refraction", &d_value))
		scene->object[i].material.refraction = 0;
	else
		scene->object[i].material.refraction = (float)d_value;
}

void				parse_material_json(int i, t_key_value *obj,
											t_scene *scene, t_rt *rt)
{
	t_array			*array;
	t_key_value		*material;
	int				value;

	if (get_node(obj, "material", &material) != 0)
	{
		set_default_value(i, scene, rt);
		return ;
	}
	if (get_array(material, "color", &array) != 0)
		scene->object[i].material.color = (cl_float3){1.f, 1.f, 1.f};
	else
	{
		parse_array_of_float(array, &scene->object[i].material.color);
		scene->object[i].material.color = cl_mult_n(scene->object[i].material.color, 1.f / 255.f);
	}
	parse_material_json1(i, material, scene);
	if (get_int(material, "texture_id", &value) || (value >= scene->texture_cnt))
		scene->object[i].material.texture_id = -1;
	else
		scene->object[i].material.texture_id = value;
}
