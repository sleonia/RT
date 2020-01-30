/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:30:28 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 23:48:26 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			show_error_in_skybox(t_rt *rt)
{
	system("osascript -e \'display notification\" \
		Used default value!\" with title \"Error skybox!\"\'");
	playSound(rt->sdl->sounds[0], 100);
	SDL_Delay(1500);
}

static void			set_default_value(t_scene *scene, t_rt *rt)
{
	scene->skybox_id = -1;
	scene->ambient = 0;
	scene->fsaa = 0;
	show_error_in_skybox(rt);
}

static void			parse_skybox_json2(t_key_value *skybox,
									t_scene *scene, t_rt *rt)
{
	double			ambient;

	scene->skybox_id = scene->texture_cnt - 1;
	if (get_double(skybox, "ambient", &ambient) != 0)
	{
		scene->ambient = 0;
		show_error_in_skybox(rt);
	}
	else
		scene->ambient = (float)ambient;
	if (get_int(skybox, "fsaa", &scene->fsaa) != 0)
	{
		scene->fsaa = 0;
		show_error_in_skybox(rt);
	}
}

void				parse_skybox_json(t_key_value *json, t_scene *scene, t_rt *rt)
{
	char			*skybox_texture;
	t_key_value		*skybox;

	if (get_node(json, "skybox", &skybox) != 0)
	{
		set_default_value(scene, rt);
		return ;
	}
	if (get_str(skybox, "texture", &skybox_texture) != 0)
	{
		scene->skybox_id = -1;
	}
	else
		if (realloc_img(scene, skybox_texture) != 0)
			ft_error("Error realloc_img");
	parse_skybox_json2(skybox, scene, rt);
}
