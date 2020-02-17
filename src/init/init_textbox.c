/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 21:27:56 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 21:29:45 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				init_textbox(t_gui *gui)
{
	int				i;

	i = -1;
	while (++i < COUNT_OF_TEXTBOX)
	{
		if (!(gui->textbox[i] = (t_textbox *)ft_memalloc(sizeof(t_textbox))))
			ft_error(ERROR_MALLOC);
		gui->textbox[i]->color = (SDL_Color){255, 255, 255, 0};
		// gui->textbox[i]->text = ft_strnew(8);
		gui->textbox[i]->text = ft_strdup("      ");
		gui->textbox[i]->on_focus = false;
		if (i == Phi)
			gui->textbox[i]->pos = (SDL_Rect){185, 50, 0, 0};
		else if (i == Tetta)
			gui->textbox[i]->pos = (SDL_Rect){390, 50, 0, 0};
		else if (i == Id)
			gui->textbox[i]->pos = (SDL_Rect){195, 190, 0, 0};
		else if (i == Skybox_ambient)
			gui->textbox[i]->pos = (SDL_Rect){260, 190, 0, 0};
		else if (i == Fsaa)
			gui->textbox[i]->pos = (SDL_Rect){395, 190, 0, 0};
		else if (i == New_obj)
		{
			gui->textbox[i]->pos = (SDL_Rect){410, 720, 0, 0};
			gui->textbox[i]->color = (SDL_Color){196, 53, 0, 0};
		}
		else if (i == Sphere_rad)
			gui->textbox[i]->pos = (SDL_Rect){185, 150, 0, 0};
		else if (i == Sphere_center)
			gui->textbox[i]->pos = (SDL_Rect){185, 200, 0, 0};
		else
			gui->textbox[i]->pos = (SDL_Rect){0, 0, 0, 0};
	}
}
