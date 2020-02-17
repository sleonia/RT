/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:09:13 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 21:32:57 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_update(char *flag, t_object **hi_lited_object, t_sdl *sdl)
{
	int		i;

	i = -1;
	*flag = *flag; //delete
	while (++i < CNT_OF_DISPLAYS)
	{
		SDL_UpdateTexture(sdl->screen[i]->texture,
						NULL, sdl->screen[i]->sur->pixels,
						(i == 0 ? WIDTH : TOOL_SCREEN_WIDTH) * sizeof(int));
		SDL_RenderCopy(sdl->screen[i]->render, sdl->screen[i]->texture,
					NULL, NULL);
		if (i == 1 && sdl->screen[1]->keyboard_focus && !*hi_lited_object) //нужно это кинуть в соответствующий gui
		{
			for (size_t k = 0; k < COUNT_OF_TEXTBOX; k++)
				render_textbox(sdl->gui->textbox[k], sdl->gui->textbox[k]->pos, sdl->screen[1]->render);
		}
		SDL_RenderPresent(sdl->screen[i]->render);
	}
}
