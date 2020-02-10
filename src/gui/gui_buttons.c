/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 09:25:09 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 15:03:37 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gui_buttons(t_sdl *sdl)
{
	sdl->gui->buttons[0]->text = "New object";
	sdl->gui->buttons[0]->clr_button = (SDL_Color){32, 82, 43, 0};
	sdl->gui->buttons[0]->rect_body = (SDL_Rect){55, 705, 400, 100};
	render_button(sdl->gui->buttons[0], sdl);

	sdl->gui->buttons[0]->text = " ";
	sdl->gui->buttons[0]->clr_button = (SDL_Color){255, 82, 43, 0};
	sdl->gui->buttons[0]->rect_body = (SDL_Rect){305, 705, 100, 100};
	render_button(sdl->gui->buttons[0], sdl);

	fill_rect((SDL_Rect){55, 800, 400, 5}, 255, sdl->screen[1]->sur);

	sdl->gui->buttons[1]->text = "Screenshot";
	sdl->gui->buttons[1]->clr_button = (SDL_Color){32, 82, 43, 0};
	sdl->gui->buttons[1]->rect_body = (SDL_Rect){55, 805, 400, 100};
	render_button(sdl->gui->buttons[1], sdl);

	fill_rect((SDL_Rect){55, 900, 400, 5}, 255, sdl->screen[1]->sur);
	sdl->gui->buttons[2]->text = "Exit";
	sdl->gui->buttons[2]->clr_button = (SDL_Color){32, 82, 43};
	sdl->gui->buttons[2]->rect_body = (SDL_Rect){55, 905, 400, 100};
	render_button(sdl->gui->buttons[2], sdl);
}
