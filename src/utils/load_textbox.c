/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 04:57:24 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 18:36:53 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			load_from_rendered_text(t_textbox *textbox,
									char *text,
									SDL_Renderer *render,
									TTF_Font *font)
{
	SDL_Surface	*txt_sur;

	if (!(txt_sur = TTF_RenderText_Solid(font, text, textbox->color)))
		ft_error((char *)SDL_GetError());
	if (!(textbox->m_texture = SDL_CreateTextureFromSurface(render, txt_sur)))
		ft_error((char *)SDL_GetError());
	textbox->m_width = txt_sur->w;
	textbox->m_height = txt_sur->h;
	SDL_FreeSurface(txt_sur);
}

void			load_textboxes(int start,
							int end,
							t_gui *gui,
							SDL_Renderer *render)
{
	int			i;

	i = start - 1;
	while (i++ <= end)
	{
		load_from_rendered_text(gui->textbox[i], gui->textbox[i]->text,
							render, gui->ttf[NORMAL_FONT_ID]->font);
	}
	if (start > New_obj)
		load_from_rendered_text(gui->textbox[New_obj],
								gui->textbox[New_obj]->text,
								render,
								gui->ttf[NORMAL_FONT_ID]->font);
}
