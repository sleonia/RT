/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textbox_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:10:54 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 21:29:23 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			change_mode(int x, int y, char *flag)
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

void			check_buttons(char *flag, int x, int y, t_rt *rt)
{
	if ((x >= 55 && x <= 350) && (y >= 705 && y <= 805))
		add_obj(88 + ft_atoi(rt->sdl->gui->textbox[New_obj]->text),
				rt->scene, rt->cl);
	if ((x >= 55 && x <= 450) && (y >= 805 && y <= 905))
		save_image(rt->sdl->screen[0]->sur->pixels);
	if ((x >= 55 && x <= 450) && (y >= 905 && y <= 1005))
		*flag = 1;
}

bool		reset_value(int flag, t_rt *rt)
{
	for (int i = 0; i < COUNT_OF_TEXTBOX; i++)
	{
		if (i != flag)
			rt->sdl->gui->textbox[i]->on_focus = false;
	}
	return (true);
}
