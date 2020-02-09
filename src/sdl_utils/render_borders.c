/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_borders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 04:17:22 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/09 05:06:07 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		render_borders(SDL_Color color, SDL_Rect rect, SDL_Surface *sur)
{
	// fill_rect((SDL_Rect){rect.x, rect.x, rect.y, rect.h},
	// 		rgb_to_int(color.r, color.g, color.b), sur);
	// fill_rect((SDL_Rect){rect.x, rect.x, rect.w, rect.y},
	// 		rgb_to_int(color.r, color.g, color.b), sur);
	// fill_rect((SDL_Rect){rect.w - rect.y, rect.x, rect.y, rect.h},
	// 		rgb_to_int(color.r, color.g, color.b), sur);
	// fill_rect((SDL_Rect){rect.x, rect.h - rect.y, rect.w, rect.y},
	// fill_rect((SDL_Rect){rect.x, rect.h - rect.y, rect.w, rect.y},
			// rgb_to_int(color.r, color.g, color.b), sur);
}
