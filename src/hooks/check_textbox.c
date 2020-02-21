/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:07:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 04:37:32 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	check_material_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 305 && x <= 480) && (y >= 360 && y <= 380)) //hueta
	{
		textbox[Mtrl_Color]->on_focus = true;
		return (reset_value(Mtrl_Color, textbox));
	}
	// else if ((x >= 305 && x <= 480) && (y >= 240 && y <= 260)) //hueta
	// {
	// 	textbox[Mtrl_ambient]->on_focus = true;
	// 	return (reset_value(Mtrl_ambient, textbox));
	// }
	// else if ((x >= 305 && x <= 480) && (y >= 240 && y <= 260)) //hueta
	// {
	// 	textbox[Mtrl_diffuse]->on_focus = true;
	// 	return (reset_value(Mtrl_diffuse, textbox));
	// }
	// else if ((x >= 305 && x <= 480) && (y >= 240 && y <= 260)) //hueta
	// {
	// 	textbox[Mtrl_specular]->on_focus = true;
	// 	return (reset_value(Mtrl_specular, textbox));
	// }
	// else if ((x >= 305 && x <= 480) && (y >= 240 && y <= 260)) //hueta
	// {
	// 	textbox[Mtrl_reflection]->on_focus = true;
	// 	return (reset_value(Mtrl_reflection, textbox));
	// }
	// else if ((x >= 305 && x <= 480) && (y >= 240 && y <= 260)) //hueta
	// {
	// 	textbox[Mtrl_refraction]->on_focus = true;
	// 	return (reset_value(Mtrl_refraction, textbox));
	// }
	// else if ((x >= 305 && x <= 480) && (y >= 240 && y <= 260)) //hueta
	// {
	// 	textbox[Mtrl_refraction]->on_focus = true;
	// 	return (reset_value(Mtrl_refraction, textbox));
	// }
	return (true);
}

static bool	check_sphere_textbox(int x, int y, t_textbox *textbox[])
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

static bool	check_cylinder_textbox(int x, int y, t_textbox *textbox[])
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

static bool	check_cone_textbox(int x, int y, t_textbox *textbox[])
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

static bool	check_plane_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Plane_tan]->on_focus = true;
		return (reset_value(Plane_tan, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Plane_axis]->on_focus = true;
		return (reset_value(Plane_axis, textbox));
	}
	return (true);
}

static bool	check_parab_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Parab_dist]->on_focus = true;
		return (reset_value(Parab_dist, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Parab_axis]->on_focus = true;
		return (reset_value(Parab_axis, textbox));
	}
	if ((x >= 35 && x <= 120) && (y >= 255 && y <= 285))
	{
		textbox[Parab_len]->on_focus = true;
		return (reset_value(Parab_len, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 255 && y <= 285))
	{
		textbox[Parab_center]->on_focus = true;
		return (reset_value(Parab_center, textbox));
	}
	return (true);
}

static bool	check_torus_textbox(int x, int y, t_textbox *textbox[])
{
	if ((x >= 35 && x <= 120) && (y >= 160 && y <= 185))
	{
		textbox[Torus_bigr]->on_focus = true;
		return (reset_value(Torus_bigr, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 160 && y <= 185))
	{
		textbox[Torus_axis]->on_focus = true;
		return (reset_value(Torus_axis, textbox));
	}
	if ((x >= 35 && x <= 120) && (y >= 255 && y <= 285))
	{
		textbox[Torus_r]->on_focus = true;
		return (reset_value(Torus_r, textbox));
	}
	if ((x >= 305 && x <= 480) && (y >= 255 && y <= 285))
	{
		textbox[Torus_center]->on_focus = true;
		return (reset_value(Torus_center, textbox));
	}
	return (true);
}

bool		check_textbox(int x, int y,
							t_object **hi_lited_object, t_textbox *textbox[])
{
	if (!*hi_lited_object)
	{
		if ((x >= 185 && x <= 275) && (y >= 60 && y <= 80))
		{
			textbox[Phi]->on_focus = true;
			return (reset_value(Phi, textbox));
		}
		if ((x >= 390 && x <= 480) && (y >= 60 && y <= 80))
		{
			textbox[Tetta]->on_focus = true;
			return (reset_value(Tetta, textbox));
		}
		if ((x >= 180 && x <= 230) && (y >= 195 && y <= 225))
		{
			textbox[Id]->on_focus = true;
			return (reset_value(Id, textbox));
		}
		if ((x >= 265 && x <= 360) && (y >= 195 && y <= 225))
		{
			textbox[Skybox_ambient]->on_focus = true;
			return (reset_value(Skybox_ambient, textbox));
		}
		if ((x >= 400 && x <= 460) && (y >= 195 && y <= 225))
		{
			textbox[Fsaa]->on_focus = true;
			return (reset_value(Fsaa, textbox));
		}	
		return (true);
	}
	else if ((*hi_lited_object)->type == o_sphere)
		check_sphere_textbox(x, y, textbox);
	else if ((*hi_lited_object)->type == o_cylinder)
		check_cylinder_textbox(x, y, textbox);
	else if ((*hi_lited_object)->type == o_cone)
		check_cone_textbox(x, y, textbox);
	else if ((*hi_lited_object)->type == o_plane)
		check_plane_textbox(x, y, textbox);
	else if ((*hi_lited_object)->type == o_parab)
		check_parab_textbox(x, y, textbox);
	else if ((*hi_lited_object)->type == o_torus)
		check_torus_textbox(x, y, textbox);
	if (*hi_lited_object)
		check_material_textbox(x, y, textbox);
	if ((x >= 410 && x <= 430) && (y >= 710 && y <= 750))
	{
		textbox[New_obj]->on_focus = true;
		return (reset_value(New_obj, textbox));
	}
	return (true);
}
