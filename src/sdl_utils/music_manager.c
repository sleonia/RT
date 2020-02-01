/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:45:43 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 03:15:34 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			change_music(Mix_Music *music[])
{
	int			index;

	Mix_PauseMusic();
	srand (time(NULL));
	index = rand() % 4;
	Mix_PlayMusic(music[0], 0);
	//переделать потом под ивенты
}
