/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:57:19 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 08:18:26 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				resize_surface(SDL_Rect srcrect, SDL_Rect dstrect,
								SDL_Surface *texture, t_sdl *sdl)
{
	srcrect.h = 0;
	srcrect.w = 0;
	srcrect.x = 0;
	srcrect.y = 0;
	SDL_BlitScaled(texture, NULL, sdl->screen[1]->sur, &dstrect);
}

void				render_surface(SDL_Rect srcrect, SDL_Rect dstrect,
								SDL_Surface *surface, t_sdl *sdl)
{
	SDL_Surface		*copy_texture;

	copy_texture = SDL_DuplicateSurface(surface);
	resize_surface(srcrect,
					dstrect,
					copy_texture, sdl);
	SDL_BlitSurface(sdl->screen[1]->sur, NULL, copy_texture, NULL);
	SDL_FreeSurface(copy_texture);
}
