/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:30:28 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 16:55:59 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_skybox_json(t_key_value *json, t_scene *scene)
{
	double			ambient;
	char			*skybox_texture;
	t_key_value		*skybox;

	if (get_node(json, "skybox", &skybox) != 0)
		ft_error("Error skybox");
	if (get_str(skybox, "texture", &skybox_texture) != 0)
		ft_error("Error skybox_texture");
	if (realloc_img(scene, skybox_texture) != 0)
		ft_error("Error realloc_img");
	if (get_double(skybox, "ambient", &ambient) != 0)
		ft_error("Error get_double: ambient");
	scene->ambient = (float)ambient;
	// if (get_double(skybox, "fsaa", &scene->fsaa) != 0)
		// ft_error("Error get_double: fsaa");	
}
