/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:55:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 08:29:16 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_flag(t_move_flag *flag)
{
	flag->w = 0;
	flag->s = 0;
	flag->d = 0;
	flag->a = 0;
	flag->v = 0;
	flag->c = 0;
}

t_scene		*init_scene(t_key_value *json, char *sounds[])
{
	t_scene	*scene;

	if ((scene = (t_scene *)ft_memalloc(sizeof(t_scene))) == NULL)
		ft_error(ERROR_INPUT);
	parse_cam_json(json, scene, sounds);
	parse_texture(json, scene);
	parse_skybox_json(json, scene, sounds);
	parse_light_json(json, scene, sounds);
	parse_objects_json(json, scene, sounds);
	init_flag(&(scene->flag));
	return (scene);
}
