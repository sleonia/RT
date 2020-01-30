/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:30:28 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 20:52:32 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			set_default_value(t_scene *scene)
{
	scene->skybox_id = -1;
	scene->ambient = 0;
	scene->fsaa = 0;
}

void				parse_skybox_json(t_key_value *json, t_scene *scene)
{
	double			ambient;
	char			*skybox_texture;
	t_key_value		*skybox;

	if (get_node(json, "skybox", &skybox) != 0)
	{
		set_default_value(scene);
		return ;
	}
	if (get_str(skybox, "texture", &skybox_texture) != 0)
	{
		set_default_value(scene);
		return ;
	}
	if (realloc_img(scene, skybox_texture) != 0)
		ft_error("Error realloc_img");
	scene->skybox_id = scene->texture_cnt - 1;
	if (get_double(skybox, "ambient", &ambient) != 0)
		scene->ambient = 0;
	else
		scene->ambient = (float)ambient;
	if (get_int(skybox, "fsaa", &scene->fsaa) != 0)
		scene->fsaa = 0;
}
