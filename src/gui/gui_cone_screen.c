/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cone_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 08:58:00 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 03:19:30 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		print_screen_title(t_ttf *ttf[], SDL_Surface *sur)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){118, 165, 163, 0};
	default_color = ttf[BIG_FONT_ID]->font_color;
	ttf[BIG_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){200, 35, 0, 0},
			"cone", ttf[BIG_FONT_ID], sur);
	ttf[BIG_FONT_ID]->font_color = default_color;
}

static void		print_screen_item(t_ttf *ttf[], SDL_Surface *sur)
{
	SDL_Color	default_color;
	SDL_Color	highlighted_color;

	highlighted_color = (SDL_Color){189, 171, 135, 0};
	default_color = ttf[NORMAL_FONT_ID]->font_color;
	ttf[NORMAL_FONT_ID]->font_color = highlighted_color;
	sdl_putstr((SDL_Rect){50, 100, 0, 0}, "length",
				ttf[NORMAL_FONT_ID], sur);
	sdl_putstr((SDL_Rect){50, 200, 0, 0}, "tan",
				ttf[NORMAL_FONT_ID], sur);
	sdl_putstr((SDL_Rect){360, 100, 0, 0}, "axis",
				ttf[NORMAL_FONT_ID], sur);
	sdl_putstr((SDL_Rect){360, 200, 0, 0}, "center",
				ttf[NORMAL_FONT_ID], sur);
	ttf[NORMAL_FONT_ID]->font_color = default_color;
}

void	gui_cone_screen(t_sdl *sdl)
{
	print_screen_title(sdl->gui->ttf, sdl->screen[1]->sur);
	print_screen_item(sdl->gui->ttf, sdl->screen[1]->sur);
	gui_material(sdl);
	gui_buttons(sdl);
	load_textboxes(Cone_axis, Cone_tan, sdl->gui, sdl->screen[1]->render);
}
