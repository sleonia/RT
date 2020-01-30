/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:25:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 20:29:34 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_material_sphere_json(t_key_value *obj_json,
											t_sphere *obj)
{
	t_array			*array;
	t_key_value		*material_node;
	double			double_value;
	char			*str_value;
	void			*obj;
	// union u_objects	object;

	if (get_node(obj_json, "material", &material_node) != 0)
		ft_error("Error get_node: material_node");
	if (get_array(material_node, "color", &array) != 0)
		ft_error("Error get_array: color");
}

void			*parse_material_cylinder_json(t_key_value *obj_json,
												t_cylinder *obj)
{

}

void			*parse_material_cone_json(t_key_value *obj_json,
											t_cone *obj)
{

}

void			*parse_material_plane_json(t_key_value *obj_json,
											t_plane *obj)
{

}
