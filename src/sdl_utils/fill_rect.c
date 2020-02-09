/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:50:14 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/09 04:28:15 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fill_rect(SDL_Rect tmp, int color, SDL_Surface *sur)
{
	SDL_Rect	rect;

	rect.x = tmp.x;
	rect.y = tmp.y;
	rect.h = tmp.h;
	rect.w = tmp.w;
	SDL_FillRect(sur, &rect, color);
}
