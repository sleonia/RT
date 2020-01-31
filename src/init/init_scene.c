/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:55:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/31 08:44:46 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		*init_scene(t_key_value *json, t_rt *rt)
{
	t_scene	*scene;

	//protect malloc
	scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	//rt содержит scene????
	parse_cam_json(json, scene, rt);
	parse_texture(json, scene, rt);
	parse_skybox_json(json, scene, rt);
	parse_light_json(json, scene, rt);
	parse_objects_json(json, scene, rt);
	return (scene);
}