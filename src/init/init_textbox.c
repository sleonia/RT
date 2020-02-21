/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 21:27:56 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 09:48:41 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			init_textbox_2(int i, t_gui *gui)
{
	if (i == New_obj)
	{
		gui->textbox[i]->pos = (SDL_Rect){420, 775, 0, 0};
		gui->textbox[i]->color = (SDL_Color){196, 53, 0, 0};
	}
	else if (i == Sphere_rad || i == Cylinder_len || i == Cone_len
		|| i == Plane_tan || i == Parab_dist || i == Torus_bigr)
		gui->textbox[i]->pos = (SDL_Rect){35, 150, 0, 0};
	else if (i == Cylinder_rad || i == Cone_tan
		|| i == Parab_len || i == Torus_r)
		gui->textbox[i]->pos = (SDL_Rect){35, 250, 0, 0};
	else if (i == Sphere_center || i == Cone_axis || i == Cylinder_axis
		|| i == Plane_axis || i == Parab_axis || i == Torus_axis)
		gui->textbox[i]->pos = (SDL_Rect){315, 150, 0, 0};
	else if (i == Cylinder_center || i == Cone_center
		|| i == Parab_center || i == Torus_center)
		gui->textbox[i]->pos = (SDL_Rect){315, 250, 0, 0};
	else
		gui->textbox[i]->pos =
			(SDL_Rect){315, 350 + (i - Mtrl_Color) * 50, 0, 0};
}

void				init_textbox(t_gui *gui)
{
	int				i;

	i = -1;
	while (++i < COUNT_OF_TEXTBOX)
	{
		if (!(gui->textbox[i] = (t_textbox *)ft_memalloc(sizeof(t_textbox))))
			ft_error(ERROR_MALLOC);
		gui->textbox[i]->color = (SDL_Color){255, 255, 255, 0};
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
		else
			init_textbox_2(i, gui);
	}
}
