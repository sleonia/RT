/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_set_value2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:38:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 17:04:00 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			set_value_in_cylinder_textbox(t_cylinder *cylinder,
									t_textbox *textbox[])
{
	char		*tmp;

	ft_strdel(&textbox[Cylinder_axis]->text);
	tmp = float_array_to_string(cylinder->axis);
	textbox[Cylinder_axis]->text = tmp;
	ft_strdel(&textbox[Cylinder_center]->text);
	tmp = float_array_to_string(cylinder->center);
	textbox[Cylinder_center]->text = tmp;
	sprintf(textbox[Cylinder_len]->text, "%3.3f", cylinder->length);
	sprintf(textbox[Cylinder_rad]->text, "%3.3f", cylinder->radius);
}

void			set_value_in_cone_textbox(t_cone *cone,
									t_textbox *textbox[])
{
	char		*tmp;

	ft_strdel(&textbox[Cone_axis]->text);
	tmp = float_array_to_string(cone->axis);
	textbox[Cone_axis]->text = tmp;
	ft_strdel(&textbox[Cone_center]->text);
	tmp = float_array_to_string(cone->center);
	textbox[Cone_center]->text = tmp;
	sprintf(textbox[Cone_len]->text, "%3.3f", cone->length);
	sprintf(textbox[Cone_tan]->text, "%3.3f", cone->tan);
}

void			set_value_in_plane_textbox(t_plane *plane,
									t_textbox *textbox[])
{
	char		*tmp;

	ft_strdel(&textbox[Plane_axis]->text);
	tmp = float_array_to_string(plane->axis);
	textbox[Plane_axis]->text = tmp;
	sprintf(textbox[Plane_tan]->text, "%3.3f", plane->dist);
}

void			set_value_in_parab_textbox(t_parab *parab,
									t_textbox *textbox[])
{
	char		*tmp;

	ft_strdel(&textbox[Parab_axis]->text);
	tmp = float_array_to_string(parab->axis);
	textbox[Parab_axis]->text = tmp;
	ft_strdel(&textbox[Parab_center]->text);
	tmp = float_array_to_string(parab->center);
	textbox[Parab_center]->text = tmp;
	sprintf(textbox[Parab_dist]->text, "%3.3f", parab->k);
	sprintf(textbox[Parab_len]->text, "%3.3f", parab->length);
}

void			set_value_in_torus_textbox(t_torus *torus,
									t_textbox *textbox[])
{
	char		*tmp;

	ft_strdel(&textbox[Torus_axis]->text);
	tmp = float_array_to_string(torus->axis);
	textbox[Torus_axis]->text = tmp;
	ft_strdel(&textbox[Torus_center]->text);
	tmp = float_array_to_string(torus->center);
	textbox[Torus_center]->text = tmp;
	sprintf(textbox[Torus_bigr]->text, "%3.3f", torus->bigr);
	sprintf(textbox[Torus_r]->text, "%3.3f", torus->r);
}
