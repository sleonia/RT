/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:09:13 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 16:17:16 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_update(t_sdl *sdl)
{
	if (sdl->help_screen_flag)
		render_help_screen(sdl);
	SDL_UpdateTexture(sdl->texture, NULL, sdl->sur->pixels,
				WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
}
