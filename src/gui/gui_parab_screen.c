/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parab_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:58:49 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 11:38:11 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_parab_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	sdl_putstr((SDL_Rect){15, 175, 0, 0}, "parab", sdl->gui->ttf[1], sdl->screen[1]->sur);

	sdl_putstr((SDL_Rect){190, 300, 0, 0}, "axis", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 400, 0, 0}, "center", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 500, 0, 0}, "distance", sdl->gui->ttf[1], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 600, 0, 0}, "length", sdl->gui->ttf[1], sdl->screen[1]->sur);
	gui_buttons(sdl);
}
