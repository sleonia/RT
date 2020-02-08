/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:32:43 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 05:02:25 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_quit(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->screen[0]->texture);
	SDL_DestroyRenderer(sdl->screen[0]->render);
	SDL_DestroyWindow(sdl->screen[0]->win);
	SDL_DestroyRenderer(sdl->screen[1]->render);
	SDL_DestroyWindow(sdl->screen[1]->win);
	endAudio();
	SDL_Quit();
}
