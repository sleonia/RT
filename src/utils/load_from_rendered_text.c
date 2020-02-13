/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_rendered_text.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 04:57:24 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/13 04:57:34 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			load_from_rendered_text(t_textbox *textbox,
									char *text,
									SDL_Renderer *render,
									TTF_Font *font)
{
	SDL_Surface	*txt_sur;

	if (!(txt_sur = TTF_RenderText_Solid(font, text, (SDL_Color){0, 0, 0, 0})))
		ft_error((char *)SDL_GetError());
	if (!(textbox->m_texture = SDL_CreateTextureFromSurface(render, txt_sur)))
		ft_error((char *)SDL_GetError());
	textbox->m_width = txt_sur->w;
	textbox->m_height = txt_sur->h;
	SDL_FreeSurface(txt_sur);
}
