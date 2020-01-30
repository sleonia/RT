/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:19:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 17:48:07 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_sphere_json(t_key_value *obj, t_sphere *sphere)
{
	double		value;
	t_array		*pos;

	if (get_double(obj, "radius", &value))
		ft_error("Error get_double: radius");
	sphere->radius = value;
	if (get_array(obj, "center", &pos))
		ft_error("Error get_array: center");
	sphere->center = **(cl_float3 **)(pos->value);
}

void			parse_plane_json(t_key_value *obj, t_plane *plane)
{
	double		value;
	t_array		*pos;

	if (get_array(obj, "axis", &pos))
		ft_error("Error get_array: axis");
	plane->axis = **(cl_float3 **)(pos->value);
	if (get_double(obj, "dist", &value))
		ft_error("Error get_double: dist");
	plane->dist = value;
}

void			parse_cone_json(t_key_value *obj, t_cone *cone)
{
	double		value;
	t_array		*pos;

	if (get_array(obj, "center", &pos))
		ft_error("Error get_array: center");
	cone->center = **(cl_float3 **)(pos->value);
	if (get_array(obj, "axis", &pos))
		ft_error("Error get_array: axis");
	cone->axis = **(cl_float3 **)(pos->value);
	if (get_double(obj, "length", &value))
		ft_error("Error get_double: length");
	cone->length = value;
	if (get_double(obj, "tan", &value))
		ft_error("Error get_double: tan");
	cone->tan = value;
}

void			parse_cylinder_json(t_key_value *obj, t_cylinder *cylinder)
{
	double		value;
	t_array		*pos;

	if (get_array(obj, "center", &pos))
		ft_error("Error get_array: center");
	cylinder->center = **(cl_float3 **)(pos->value);
	if (get_array(obj, "axis", &pos))
		ft_error("Error get_array: axis");
	cylinder->axis = **(cl_float3 **)(pos->value);
	if (get_double(obj, "length", &value))
		ft_error("Error get_double: length");
	cylinder->length = value;
	if (get_double(obj, "radius", &value))
		ft_error("Error get_double: radius");
	cylinder->radius = value;
}
