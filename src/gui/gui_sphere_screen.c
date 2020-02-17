/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sphere_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:47:21 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 15:18:59 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_sphere_screen(t_sdl *sdl, t_object **hi_lited_object)
{
	sdl_putstr((SDL_Rect){190, 35, 0, 0}, "sphere", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);

	sdl_putstr((SDL_Rect){190, 200, 0, 0}, "radius", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){190, 300, 0, 0}, "center", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	gui_material(sdl, hi_lited_object);
	// sdl_putstr((SDL_Rect){190, 35, 0, 0}, "sphere", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	// sdl_putstr((SDL_Rect){190, 35, 0, 0}, "sphere", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	// sdl_putstr((SDL_Rect){190, 35, 0, 0}, "sphere", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	// sdl_putstr((SDL_Rect){190, 35, 0, 0}, "sphere", sdl->gui->ttf[BIG_FONT_ID], sdl->screen[1]->sur);
	gui_buttons(sdl);
}
