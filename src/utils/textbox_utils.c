/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textbox_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:10:54 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 11:30:19 by sleonia          ###   ########.fr       */
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
	if ((x >= 200 && x <= 300) && (y >= 410 && y <= 430))
		*flag = RED_MASK;
	if ((x >= 350 && x <= 410) && (y >= 410 && y <= 430))
		*flag = GREEN_MASK;
	if ((x >= 200 && x <= 300) && (y >= 440 && y <= 465))
		*flag = BLUE_MASK;
}

void			check_buttons(int x, int y,
							t_object **hi_lited_object, t_rt *rt)
{
	if ((x >= 260 && x <= 460) && (y >= 700 && y <= 765))
		*hi_lited_object = NULL;
	if ((x >= 55 && x <= 255) && (y >= 700 && y <= 765))
		SDL_ShowCursor(1);
	if ((x >= 55 && x <= 405) && (y >= 770 && y <= 830))
	{
		add_obj(88 + ft_atoi(rt->sdl->gui->textbox[New_obj]->text),
				rt->scene, rt->cl);
	}
	if ((x >= 55 && x <= 450) && (y >= 835 && y <= 895))
		save_image(rt->sdl->screen[0]->sur->pixels);
	if ((x >= 55 && x <= 455) && (y >= 900 && y <= 960))
		exit(1);
}

bool			reset_value(int flag, t_textbox *textbox[])
{
	int		i;

	i = 0;
	while (i < COUNT_OF_TEXTBOX)
	{
		if (i != flag)
			textbox[i]->on_focus = false;
		i++;
	}
	return (true);
}
