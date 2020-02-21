/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 09:25:09 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 09:31:48 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gui_buttons(t_sdl *sdl)
{
	sdl->gui->buttons[0]->text = "Choose";
	sdl->gui->buttons[0]->clr_button = (SDL_Color){24, 15, 55, 0};
	sdl->gui->buttons[0]->rect_body = (SDL_Rect){55, 700, 198, 60};
	render_button(sdl->gui->buttons[0], sdl);

	sdl->gui->buttons[1]->text = "Reset choose";
	sdl->gui->buttons[1]->clr_button = (SDL_Color){24, 15, 55, 0};
	sdl->gui->buttons[1]->rect_body = (SDL_Rect){258, 700, 197, 60};
	render_button(sdl->gui->buttons[1], sdl);

	sdl->gui->buttons[2]->text = "New object";
	sdl->gui->buttons[2]->clr_button = (SDL_Color){24, 15, 55, 0};
	sdl->gui->buttons[2]->rect_body = (SDL_Rect){55, 765, 400, 60};
	render_button(sdl->gui->buttons[2], sdl);

	sdl->gui->buttons[3]->text = "Screenshot";
	sdl->gui->buttons[3]->clr_button = (SDL_Color){24, 15, 55, 0};
	sdl->gui->buttons[3]->rect_body = (SDL_Rect){55, 830, 400, 60};
	render_button(sdl->gui->buttons[3], sdl);

	sdl->gui->buttons[4]->text = "Exit";
	sdl->gui->buttons[4]->clr_button = (SDL_Color){24, 15, 55, 0};
	sdl->gui->buttons[4]->rect_body = (SDL_Rect){55, 895, 400, 60};
	render_button(sdl->gui->buttons[4], sdl);
}
