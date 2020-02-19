/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:27:18 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 15:27:35 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_parab_json(t_key_value *obj, t_parab *parab)
{
	double		value;
	t_array		*pos;

	if (get_array(obj, "center", &pos))
		ft_error("Error get_array: center");
	parse_array_of_float(pos, &parab->center);
	if (get_array(obj, "axis", &pos))
		ft_error("Error get_array: axis");
	parse_array_of_float(pos, &parab->axis);
	cl_normalize(&parab->axis);
	if (get_double(obj, "distance", &value))
		ft_error("Error get_double: distance");
	parab->k = (float)value;
	if (get_double(obj, "length", &value))
		ft_error("Error get_double: distance");
	parab->length = (float)value;
}

void			parse_torus_json(t_key_value *obj, t_torus *tor)
{
	double		value;
	t_array		*pos;

	if (get_array(obj, "center", &pos))
		ft_error("Error get_array: center");
	parse_array_of_float(pos, &tor->center);
	if (get_array(obj, "axis", &pos))
		ft_error("Error get_array: axis");
	parse_array_of_float(pos, &tor->axis);
	cl_normalize(&tor->axis);
	if (get_double(obj, "bigr", &value))
		ft_error("Error get_double: bigr");
	tor->bigr = (float)value;
	if (get_double(obj, "r", &value))
		ft_error("Error get_double: r");
	tor->r = (float)value;
}
