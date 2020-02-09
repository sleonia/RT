/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 04:26:16 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/09 06:45:03 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		render_button(t_button *button, t_sdl *sdl)
{
	fill_rect(button->rect_borders, rgb_to_int(button->clr_border.r, button->clr_border.g, button->clr_border.b), sdl->screen[1]->sur);
	fill_rect(button->rect_body, rgb_to_int(button->clr_button.r, button->clr_button.g, button->clr_button.b), sdl->screen[1]->sur);
	sdl_putstr((SDL_Rect){button->rect_body.x, button->rect_body.y}, button->text, sdl->gui->ttf[1], sdl->screen[1]->sur);
}
