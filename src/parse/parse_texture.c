/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:52:50 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 03:18:43 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_texture(t_key_value *json, t_scene *scene,
								char *sounds[])
{
	int				i;
	t_array			*texture_array;
	char			*path;

	i = -1;
	if (get_array(json, "textures", &texture_array) != 0)
		ft_error("Error textures");
	while (++i < texture_array->length)
	{
		if (getf_str_array(texture_array, i, &path) != 0)
			ft_error("Can't find texture");
		else if (realloc_img(scene, path) != 0)
			ft_error("Can't realloc image");
		// ft_strdel(&path);
	}
}
