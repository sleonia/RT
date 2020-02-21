/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textbox2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:21:53 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 13:28:29 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	check_material_textbox2(int x, int y, t_textbox *textbox[])
{
	if ((x >= 305 && x <= 480) && (y >= 560 && y <= 580))
	{
		textbox[Mtrl_reflection]->on_focus = true;
		return (reset_value(Mtrl_reflection, textbox));
	}
	else if ((x >= 305 && x <= 480) && (y >= 610 && y <= 630))
	{
		textbox[Mtrl_refraction]->on_focus = true;
		return (reset_value(Mtrl_refraction, textbox));
	}
	else if ((x >= 305 && x <= 480) && (y >= 660 && y <= 680))
	{
		textbox[Mtrl_texture_id]->on_focus = true;
		return (reset_value(Mtrl_texture_id, textbox));
	}
	return (true);
}

bool		check_material_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 305 && x <= 480) && (y >= 360 && y <= 380))
	{
		textbox[Mtrl_Color]->on_focus = true;
		return (reset_value(Mtrl_Color, textbox));
	}
	else if ((x >= 305 && x <= 480) && (y >= 410 && y <= 430))
	{
		textbox[Mtrl_ambient]->on_focus = true;
		return (reset_value(Mtrl_ambient, textbox));
	}
	else if ((x >= 305 && x <= 480) && (y >= 460 && y <= 480))
	{
		textbox[Mtrl_diffuse]->on_focus = true;
		return (reset_value(Mtrl_diffuse, textbox));
	}
	else if ((x >= 305 && x <= 480) && (y >= 510 && y <= 530))
	{
		textbox[Mtrl_specular]->on_focus = true;
		return (reset_value(Mtrl_specular, textbox));
	}
	check_material_textbox2(x, y, textbox);
	return (true);
}

bool		check_sphere_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Sphere_rad]->on_focus = true;
		return (reset_value(Sphere_rad, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Sphere_center]->on_focus = true;
		return (reset_value(Sphere_center, textbox));
	}
	return (true);
}

bool		check_cylinder_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Cylinder_len]->on_focus = true;
		return (reset_value(Cylinder_len, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Cylinder_axis]->on_focus = true;
		return (reset_value(Cylinder_axis, textbox));
	}
	if ((x >= 35 && x <= 120) && (y >= 255 && y <= 285))
	{
		textbox[Cylinder_rad]->on_focus = true;
		return (reset_value(Cylinder_rad, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 255 && y <= 285))
	{
		textbox[Cylinder_center]->on_focus = true;
		return (reset_value(Cylinder_center, textbox));
	}
	return (true);
}

bool		check_cone_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Cone_len]->on_focus = true;
		return (reset_value(Cone_len, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Cone_axis]->on_focus = true;
		return (reset_value(Cone_axis, textbox));
	}
	if ((x >= 35 && x <= 120) && (y >= 255 && y <= 285))
	{
		textbox[Cone_tan]->on_focus = true;
		return (reset_value(Cone_tan, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 255 && y <= 285))
	{
		textbox[Cone_center]->on_focus = true;
		return (reset_value(Cone_center, textbox));
	}
	return (true);
}
