/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:55:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 17:03:44 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		*init_scene(t_key_value *json, t_rt *rt)
{
	t_scene	*scene;

	scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	parse_cam_json(json, scene);
	parse_skybox_json(json, scene);
	parse_light_json(json, scene);
	parse_objects_json(json, scene);
	return (scene);
}