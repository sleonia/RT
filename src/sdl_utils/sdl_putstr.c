/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:48:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 14:33:11 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sdl_putstr(SDL_Rect rect, char *text,
						t_ttf *ttf, SDL_Surface *sur)
{
	SDL_Surface	*txt_sur;

	if (!(txt_sur = TTF_RenderText_Blended(ttf->font, text,
										ttf->font_color)))
		ft_error((char *)SDL_GetError());
	SDL_BlitSurface(txt_sur, NULL, sur, &rect);
	SDL_FreeSurface(txt_sur);
}
