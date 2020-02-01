/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:49:49 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 05:53:04 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				parse_music_json(t_key_value *assets, t_sdl *sdl)
{
	int				i;
	char			*arg;
	char			*music_name;
	t_array			*music;

	i = -1;
	if (get_array(assets, "music", &music) != 0)
		ft_error("\033[31mError music\033[0m");
	while (++i < music->length)
	{
		if (!(sdl->music[i] = Mix_LoadMUS(((char **)(music->value))[i])))
			ft_error((char *)SDL_GetError());
	}
}

void				parse_sounds_json(t_key_value *assets, t_sdl *sdl)
{
	int				i;
	char			*sounds_name;
	t_array			*sounds;

	i = -1;
	if (get_array(assets, "sounds", &sounds) != 0)
		ft_error("\033[31mError sounds\033[0m");
	while (++i < sounds->length)
	{
		if (!(sdl->sounds[i] = ((char **)(sounds->value))[i]))
			ft_error((char *)SDL_GetError());
	}
}

int					parse_volume_json(t_key_value *assets)
{
	int				volume;
	t_key_value		*volume_obj;

	if (!get_int(assets, "volume", &volume))
		return (59);
	return (volume);
}

char				*parse_icon_json(t_key_value *assets, t_sdl *sdl)
{
	char			*icon_name;
	t_key_value		*icons;

	if (get_str(assets, "icon", &icon_name) != 0)
		return (NULL);
	return (icon_name);
}

t_key_value			*parse_assets(t_key_value *json, t_sdl *sdl)
{
	t_key_value		*assets;

	if (get_node(json, "assets", &assets) != 0)
		ft_error("\033[31mError assets\033[0m");
	return (assets);
}
