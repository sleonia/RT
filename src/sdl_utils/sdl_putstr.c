/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:48:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 06:50:04 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sdl_putstr(int x, int y, char *text, t_sdl *sdl)
{
	SDL_Rect	dest;
	SDL_Surface	*txt_sur;

	dest.x = x;
	dest.y = y;
	txt_sur = TTF_RenderText_Blended(sdl->font, text,
										sdl->font_color);
	SDL_BlitSurface(txt_sur, NULL, sdl->screen[1]->sur, &dest);
	SDL_FreeSurface(txt_sur);
}
