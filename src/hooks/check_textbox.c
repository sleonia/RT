/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:07:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 13:31:03 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		check_plane_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Plane_tan]->on_focus = true;
		reset_value(Plane_tan, textbox);
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Plane_axis]->on_focus = true;
		reset_value(Plane_axis, textbox);
	}
}

static void		check_parab_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Parab_dist]->on_focus = true;
		reset_value(Parab_dist, textbox);
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Parab_axis]->on_focus = true;
		reset_value(Parab_axis, textbox);
	}
	if ((x >= 35 && x <= 120) && (y >= 255 && y <= 285))
	{
		textbox[Parab_len]->on_focus = true;
		reset_value(Parab_len, textbox);
	}
	if ((x >= 305 && x <= 480) && (y >= 255 && y <= 285))
	{
		textbox[Parab_center]->on_focus = true;
		reset_value(Parab_center, textbox);
	}
}

static void		check_torus_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Torus_bigr]->on_focus = true;
		reset_value(Torus_bigr, textbox);
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Torus_axis]->on_focus = true;
		reset_value(Torus_axis, textbox);
	}
	if ((x >= 35 && x <= 120) && (y >= 255 && y <= 285))
	{
		textbox[Torus_r]->on_focus = true;
		reset_value(Torus_r, textbox);
	}
	if ((x >= 305 && x <= 480) && (y >= 255 && y <= 285))
	{
		textbox[Torus_center]->on_focus = true;
		reset_value(Torus_center, textbox);
	}
}

static void		check_def_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 185 && x <= 275) && (y >= 60 && y <= 80))
	{
		textbox[Phi]->on_focus = true;
		reset_value(Phi, textbox);
	}
	if ((x >= 390 && x <= 480) && (y >= 60 && y <= 80))
	{
		textbox[Tetta]->on_focus = true;
		reset_value(Tetta, textbox);
	}
	if ((x >= 180 && x <= 230) && (y >= 195 && y <= 225))
	{
		textbox[Id]->on_focus = true;
		reset_value(Id, textbox);
	}
	if ((x >= 265 && x <= 360) && (y >= 195 && y <= 225))
	{
		textbox[Skybox_ambient]->on_focus = true;
		reset_value(Skybox_ambient, textbox);
	}
	if ((x >= 400 && x <= 460) && (y >= 195 && y <= 225))
	{
		textbox[Fsaa]->on_focus = true;
		reset_value(Fsaa, textbox);
	}
}

bool			check_textbox(int x, int y,
							t_object **select_obj, t_textbox *textbox[])
{
	if (!*select_obj)
		check_def_textbox(x, y, textbox);
	else if ((*select_obj)->type == o_sphere)
		check_sphere_textbox(x, y, textbox);
	else if ((*select_obj)->type == o_cylinder)
		check_cylinder_textbox(x, y, textbox);
	else if ((*select_obj)->type == o_cone)
		check_cone_textbox(x, y, textbox);
	else if ((*select_obj)->type == o_plane)
		check_plane_textbox(x, y, textbox);
	else if ((*select_obj)->type == o_parab)
		check_parab_textbox(x, y, textbox);
	else if ((*select_obj)->type == o_torus)
		check_torus_textbox(x, y, textbox);
	if (*select_obj)
		check_material_textbox(x, y, textbox);
	if ((x >= 410 && x <= 460) && (y >= 770 && y <= 830))
	{
		textbox[New_obj]->on_focus = true;
		reset_value(New_obj, textbox);
	}
	return (true);
}
