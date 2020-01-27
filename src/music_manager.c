/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:45:43 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/27 11:49:38 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			change_music(t_rt *rt)
{
	int			index;

	Mix_PauseMusic();
	srand (time(NULL));
	index = rand() % 4;
	Mix_PlayMusic(rt->sdl->music[index], 0);
}
