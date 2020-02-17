/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_plane_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:58:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 11:39:36 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_plane_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	sdl_putstr((SDL_Rect){15, 175, 0, 0}, "plane", sdl->gui->ttf[1], sdl->screen[1]->sur);

	sdl_putstr((SDL_Rect){15, 300, 0, 0}, "axis", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){15, 400, 0, 0}, "distance", sdl->gui->ttf[1], sdl->screen[1]->sur);	
	gui_buttons(sdl);
}
