/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:49:49 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 20:34:33 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_songs_json(t_key_value *assets, t_sdl *sdl)
{
	int				i;
	char			*arg;
	char			*songs_name;
	t_key_value		*songs;

	i = -1;
	if (get_node(assets, "songs", &songs) != 0)
		ft_error("Error songs");
	songs_name = ft_strdup("song_0");
	while (get_str(songs, songs_name, &arg) == 0)
	{
		if (!arg)
			ft_error("Error arg");
		if (!(sdl->music[++i] = Mix_LoadMUS(arg)))
			ft_error((char *)SDL_GetError());
		if (!(songs_name = get_next_name(songs_name)))
			ft_error("Error songs_name");
		ft_strdel(&arg);
	}
	ft_strdel(&songs_name);
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
	char			*texture_name;
	t_key_value		*icons;

	if (get_node(assets, "icons", &icons) != 0)
		ft_error("Error icons");
	if (get_str(icons, "icon_0", &texture_name) != 0)
		ft_error("Error icon_0");
	return (texture_name);
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
