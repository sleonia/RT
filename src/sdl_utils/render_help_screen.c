/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_help_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:37:03 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/05 17:56:02 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	resize_surface(SDL_Rect srcrect, SDL_Rect dstrect,
					SDL_Surface *texture, t_sdl *sdl)
{
	// if (env->sdl->resize_flag == 0)
	// 	SDL_BlitScaled(texture, &srcrect, env->sdl->sur, &dstrect);
	// else if (env->sdl->resize_flag == 1)
	SDL_BlitScaled(texture, NULL, sdl->sur, &dstrect);
	// else if (env->sdl->resize_flag == 2)
	// 	SDL_BlitScaled(texture, &srcrect, env->sdl->sur, NULL);
}

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
	SDL_Surface *copy = SDL_DuplicateSurface(sdl->sur);
	SDL_Surface *copy1 = SDL_CreateRGBSurface(0, WIDTH,
			HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t k = 0; k < WIDTH; k++)
		{
			// ((int *)(sdl->sur->pixels))[i * WIDTH + k] = 0xFACF;
			((int *)(copy1->pixels))[i * WIDTH + k] = 0xF;
		}
	}
	// write_text(100, 100, "Use ESC for exiting", sdl);
	// write_text(100, 130, "Use N for negative mode", sdl);
	// write_text(100, 160, "Use M for sepia mode", sdl);
	// write_text(100, 190, "Use B for default mode", sdl);
	// write_text(100, 220, "Use H for clean/show help screen", sdl);
	// write_text(100, 250, "Use 0-3 on numpad for adding objects", sdl);
	// write_text(100, 280, "Use w/a/s/d for moving", sdl);
	// write_text(100, 310, "Use q/e/z/c for rotation", sdl);

	// SDL_Rect srcrect = {0, 0, HEIGHT, WIDTH};
	// SDL_Rect dstrect = {100, 100, HEIGHT - 100, WIDTH - 100};
	// // SDL_Surface *copy = SDL_DuplicateSurface(sdl->sur);
	// resize_surface(srcrect, dstrect, copy, sdl);


	SDL_Rect	rect;
	SDL_Rect	dest;

	rect.x = 0;
	rect.y = 0;
	rect.w = WIDTH;
	rect.h = HEIGHT;
	dest.x = 200;
	dest.y = 200;
	dest.w = 300;
	dest.h = 300;
	// SDL_BlitScaled(copy, &rect, sdl->sur, &dest);
	SDL_BlitScaled(copy, &rect, copy1, &dest);
	// SDL_BlitScaled(sdl->sur, &rect, sdl->sur, &dest);
	SDL_FreeSurface(sdl->sur);
	sdl->sur = copy;
	
	// resize_surface(srcrect, dstrect, copy, sdl->sur);
	// write_text(100, 130, "Hold down the left mouse button and move the mouse", sdl);
	// write_text(100, 100, "LOX", sdl);
	return (0);
}
