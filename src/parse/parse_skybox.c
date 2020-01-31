/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:30:28 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/31 07:52:03 by deladia          ###   ########.fr       */
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
	int				texture_id;
	t_key_value		*skybox;

	if (get_node(json, "skybox", &skybox) != 0)
	{
		set_default_value(scene, rt);
		return ;
	}
	if (get_int(skybox, "texture_id", &texture_id) || (texture_id >= scene->texture_cnt))
		scene->skybox_id = -1;
	else
		scene->skybox_id = texture_id;
	parse_skybox_json2(skybox, scene, rt);
}
