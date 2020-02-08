/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_default_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:44:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 07:48:39 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Texture	*texture;

static void	 load_from_rendered_text(SDL_Renderer *render, TTF_Font *font,
									const char *str, SDL_Color color)
{
	SDL_Surface	*txt_surface;
	// SDL_Texture	*texture;

	txt_surface = TTF_RenderText_Solid(font, str, color);
	texture = SDL_CreateTextureFromSurface(render, txt_surface);
	SDL_FreeSurface(txt_surface);
}

void		gui_default_screen(t_object **hi_lited_object, t_sdl *sdl)
{
	load_from_rendered_text(sdl->screen[1]->render, sdl->font, "SOSU", (SDL_Color){255, 255, 0, 0});
	load_from_rendered_text(sdl->screen[1]->render, sdl->font, (const char *)sdl->gui->input_text, (SDL_Color){255, 255, 0, 0});
	SDL_StartTextInput();
	// sdl_putstr(100, 100, "PIDOR", sdl);
}
