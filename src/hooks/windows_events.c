/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 02:39:27 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 11:02:24 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool		window_events(char *flag, SDL_Event event, t_screen *screen)
{
	if (!(event.type == SDL_WINDOWEVENT
		&& event.window.windowID == (Uint32)screen->win_id))
		return (false);
	if (event.window.event == SDL_WINDOWEVENT_SHOWN)
		screen->shown = true;
	if (event.window.event == SDL_WINDOWEVENT_HIDDEN)
		screen->shown = true;
	if (event.window.event == SDL_WINDOWEVENT_ENTER)
		screen->mouse_focus = true;
	if (event.window.event == SDL_WINDOWEVENT_LEAVE)
	{
		if (screen->win_id == 1)
			SDL_ShowCursor(1);
		screen->mouse_focus = false;
	}
	if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		screen->keyboard_focus = true;
	if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		screen->keyboard_focus = false;
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		*flag = 1;
	return (true);
}
