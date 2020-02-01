/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:32:43 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 11:33:16 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_quit(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	endAudio();
	SDL_Quit();
}
