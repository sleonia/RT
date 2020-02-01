/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:30:28 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 04:16:29 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			set_default_value(t_scene *scene, char *sounds[])
{
	scene->skybox_id = -1;
	scene->ambient = 0;
	scene->fsaa = 0;
	show_error(E_SKYBOX, sounds);
}

static void			parse_skybox_json2(t_key_value *skybox,
									t_scene *scene, char *sounds[])
{
	double			ambient;

	if (get_double(skybox, "ambient", &ambient) != 0)
	{
		scene->ambient = 0;
		show_error(E_SKYBOX, sounds);
	}
	else
		scene->ambient = (float)ambient;
	if (get_int(skybox, "fsaa", &scene->fsaa) != 0)
	{
		scene->fsaa = 0;
		show_error(E_SKYBOX, sounds);
	}
}

void				parse_skybox_json(t_key_value *json, t_scene *scene,
									char *sounds[])
{
	int				texture_id;
	t_key_value		*skybox;

	if (get_node(json, "skybox", &skybox) != 0)
	{
		set_default_value(scene, sounds);
		return ;
	}
	if (get_int(skybox, "texture_id", &texture_id)
		|| (texture_id >= scene->texture_cnt))
		scene->skybox_id = -1;
	else
		scene->skybox_id = texture_id;
	parse_skybox_json2(skybox, scene, sounds);
}
