/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:09:13 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/13 05:06:27 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_update(char *flag, t_object **hi_lited_object, t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->screen[0]->texture, NULL,
					sdl->screen[0]->sur->pixels, WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->screen[0]->render, sdl->screen[0]->texture,
				NULL, NULL);
	SDL_RenderPresent(sdl->screen[0]->render);



	SDL_UpdateTexture(sdl->screen[1]->texture, NULL,
					sdl->screen[1]->sur->pixels, 500 * sizeof(int));
	SDL_RenderCopy(sdl->screen[1]->render, sdl->screen[1]->texture,
				NULL, NULL);
	render_textbox(sdl->gui->textbox[0], 185, 50, sdl->screen[1]->render);
	render_textbox(sdl->gui->textbox[1], 185, 50, sdl->screen[1]->render);
	SDL_RenderPresent(sdl->screen[1]->render);
}
