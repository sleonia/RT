/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:01:21 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 12:04:05 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					render_one_textbox(t_textbox *textbox,
										SDL_Renderer *render)
{
	SDL_Rect			*clip;
	double				angle;
	SDL_Point			*center;
	SDL_RendererFlip	flip;
	SDL_Rect			render_quad;

	clip = NULL;
	angle = 0;
	center = NULL;
	flip = SDL_FLIP_NONE;
	render_quad = (SDL_Rect){textbox->pos.x, textbox->pos.y,
							textbox->m_width, textbox->m_height};
	if(clip != NULL)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopyEx(render, textbox->m_texture, clip, &render_quad, angle, center, flip);
}

void					render_textboxs(int start,
										int end,
										t_gui *gui,
										SDL_Renderer *render)
{
	int					i;

	i = start;
	while (i <= end)
	{
		render_one_textbox(gui->textbox[i], render);
		i++;
	}
	if (start > New_obj)
		render_one_textbox(gui->textbox[New_obj], render);
}
