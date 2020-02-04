/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_help_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:37:03 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 16:55:24 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			write_text(int x, int y, char *text, t_sdl *sdl)
{
	SDL_Rect	dest;
	SDL_Surface	*txt_sur;

	dest.x = x;
	dest.y = y;
	txt_sur = TTF_RenderText_Blended(sdl->font, text,
										sdl->font_color);
	SDL_BlitSurface(txt_sur, NULL, sdl->sur, &dest);
	SDL_FreeSurface(txt_sur);
}

int			render_help_screen(t_sdl *sdl)
{
	// for (size_t i = 0; i < HEIGHT; i++)
	// {
	// 	for (size_t k = 0; k < WIDTH; k++)
	// 	{
	// 		((int *)(sdl->sur->pixels))[i * WIDTH + k] = 0x8b0023;
	// 	}
	// }
	write_text(100, 100, "Use ESC for exiting", sdl);
	write_text(100, 130, "Use N for negative mode", sdl);
	write_text(100, 160, "Use M for sepia mode", sdl);
	write_text(100, 190, "Use B for default mode", sdl);
	write_text(100, 220, "Use H for clean/show help screen", sdl);
	write_text(100, 250, "Use 0-3 on numpad for adding objects", sdl);
	write_text(100, 280, "Use w/a/s/d for moving", sdl);
	write_text(100, 310, "Use q/e/z/c for rotation", sdl);
	// write_text(100, 130, "Hold down the left mouse button and move the mouse", sdl);
	// write_text(100, 100, "LOX", sdl);
	return (0);
}
