/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:01:21 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/13 09:46:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static void				

void					render_textbox(t_textbox *textbox,
									SDL_Rect pos,
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
	render_quad = (SDL_Rect){pos.x, pos.y, textbox->m_width, textbox->m_height};
	if(clip != NULL)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopyEx(render, textbox->m_texture, clip, &render_quad, angle, center, flip);
}

