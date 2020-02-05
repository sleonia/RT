/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:55:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/05 18:23:21 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		*init_scene(t_key_value *json, char *sounds[])
{
	t_scene	*scene;

	if ((scene = (t_scene *)ft_memalloc(sizeof(t_scene))) == NULL)
		ft_error(ERROR_INPUT);
	parse_cam_json(json, scene, sounds);
	parse_texture(json, scene, sounds);
	parse_skybox_json(json, scene, sounds);
	parse_light_json(json, scene, sounds);
	parse_objects_json(json, scene, sounds);
	return (scene);
}
