/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:49:49 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 07:48:48 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_songs_json(t_key_value *assets, t_sdl *sdl)
{
	int				i;
	char			*arg;
	char			*songs_name;
	t_array			*songs;

	i = -1;
	if (get_array(assets, "songs", &songs) != 0)
		ft_error("Error songs");
	// printf("%zu\n", songs->length);
	while (++i < songs->length)
	{
		if (!(sdl->music[i] = Mix_LoadMUS(((char **)(songs->value))[i])))
			ft_error((char *)SDL_GetError());
	}
}

int					parse_volume_json(t_key_value *assets)
{
	int				volume;
	t_key_value		*volume_obj;

	if (!get_int(assets, "volume", &volume))
		ft_error("Error songs");
	return (volume);
}

char				*parse_icon_json(t_key_value *assets, t_sdl *sdl)
{
	char			*icon_name;
	t_key_value		*icons;

	if (get_str(assets, "icon", &icon_name) != 0)
		ft_error("Error icon");
	return (icon_name);
}

char				*parse_textures_json(t_key_value *assets, t_sdl *sdl)
{
	//что-то придумать
	return (NULL);
}

t_key_value			*parse_assets(t_key_value *json, t_sdl *sdl)
{
	t_key_value		*assets;

	if (get_node(json, "assets", &assets) != 0)
		ft_error("ERROR_INPUT1");
	return (assets);
}
