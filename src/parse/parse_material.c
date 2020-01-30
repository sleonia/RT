/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:25:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/31 00:23:40 by sleonia          ###   ########.fr       */
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
	scene->object[i].material.color = (cl_float3){255, 0, 0};
	scene->object[i].material.ambient = 0;
	scene->object[i].material.diffuse = 0;
	scene->object[i].material.specular = 0;
	scene->object[i].material.reflection = 0;
	scene->object[i].material.refraction = 0;
	scene->object[i].material.texture_id = -1;
	show_error_in_material(rt);
}

void			parse_material_json(int i, t_key_value *obj,
									t_scene *scene, t_rt *rt)
{
	t_array		*array;
	t_key_value	*material;
	bool		error;
	double		d_value;
	char		*s_value;

	error = false;
	if (get_node(obj, "material", &material) != 0)
	{
		set_default_value(i, scene, rt);
		return ;
	}
	if (get_array(material, "color", &array) != 0)
	{
		error = true;
		scene->object[i].material.color = (cl_float3){255, 0, 0};
	}
	else
		scene->object[i].material.color = **(cl_float3 **)(array->value);
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
	if (get_str(material, "texture", &s_value))
		scene->object[i].material.texture_id = -1;
	else
		realloc_img(scene, s_value);
}