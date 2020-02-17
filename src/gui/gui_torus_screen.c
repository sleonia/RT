/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_torus_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:59:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 11:36:09 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_torus_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	sdl_putstr((SDL_Rect){15, 175, 0, 0}, "torus", sdl->gui->ttf[1], sdl->screen[1]->sur);

	sdl_putstr((SDL_Rect){190, 200, 0, 0}, "axis", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 300, 0, 0}, "center", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 400, 0, 0}, "bigr", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 500, 0, 0}, "bigr", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 600, 0, 0}, "r", sdl->gui->ttf[1], sdl->screen[1]->sur);
	gui_buttons(sdl);
}