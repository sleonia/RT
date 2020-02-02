/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:45:43 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/02 12:41:22 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			change_music(Mix_Music *music[])
{
	int			id;
	int			len;

	Mix_PauseMusic();
	srand(time(NULL));
	len = ft_len_arr((void **)(music));
	if (len == 1)
		Mix_PlayMusic(music[0], 0);
	else
	{
		id = rand() % len;
	}
}
