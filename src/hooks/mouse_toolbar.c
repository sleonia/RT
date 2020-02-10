/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_toolbar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:52:23 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 11:13:37 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		change_mode(int x, int y, char *flag)
{
	if ((x >= 200 && x <= 250) && (y >= 385 && y <= 410))
		*flag = BLUR;
	if ((x >= 350 && x <= 410) && (y >= 385 && y <= 410))
		*flag = 0;
	if ((x >= 200 && x <= 300) && (y >= 350 && y <= 375))
		*flag = NEGATIVE;
	if ((x >= 350 && x <= 410) && (y >= 350 && y <= 375))
		*flag = SEPIA;
}

static void		check_buttons(char *flag, int x, int y, t_rt *rt)
{
	if ((x >= 55 && x <= 450) && (y >= 705 && y <= 805))
	{
		// add_obj(scancode, rt);
	}
	if ((x >= 55 && x <= 450) && (y >= 805 && y <= 905))
		save_image(rt->sdl->screen[0]->sur->pixels);
	if ((x >= 55 && x <= 450) && (y >= 905 && y <= 1005))
		*flag = 1;
}

bool			mouse_toolbar(char *flag,
							t_object **hi_lited_object,
							t_rt *rt)
{
	// int			i;
	int			x = -1;
	int			y = -1;

	if (rt->sdl->event.button.button == SDL_BUTTON_LEFT)
		SDL_GetMouseState(&x, &y);
	if (!hi_lited_object)
	{
		if ((x >= 200 && x <= 410) && (y >= 350 && y <= 410))
			change_mode(x, y, flag);
	}
	check_buttons(flag, x, y, rt);
	// i = -1;
	// while (++i < 4)
	// {
	if (x != -1 && y != -1)
		printf("x = %d   y = %d\n", x ,y);
	// // if ((x >= 70 && x <= 120) && (y >= 0 && y <= 36))
	// if ((x >= 70 && x <= 120) && (y >= 50 && y <= 86))
	// {
	// 	sdl->gui->radio_btn[0] = !sdl->gui->radio_btn[0];
	// }
	// if ((x >= 70 && x <= 120) && (y >= 100 && y <= 100 + 36))
	// {
	// 	sdl->gui->radio_btn[1] = !sdl->gui->radio_btn[1];
	// }
	// if ((x >= 70 && x <= 120) && (y >= 150 && y <= 150 + 36))
	// {
	// 	sdl->gui->radio_btn[2] = !sdl->gui->radio_btn[2];
	// }
	// if ((x >= 70 && x <= 120) && (y >= 200 && y <= 200 + 36))
	// {
	// 	sdl->gui->radio_btn[3] = !sdl->gui->radio_btn[3];
	// }
	// }
	// if (flag)
		// return (false);
	// if ()
	return (false);
}
