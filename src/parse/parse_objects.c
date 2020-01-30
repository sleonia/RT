/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:51:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 20:29:25 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			check_type(char *type)
{
	if (ft_strcmp(type, "sphere") == 0)
		return (o_sphere);
	else if (ft_strcmp(type, "cylinder") == 0)
		return (o_cylinder);
	else if (ft_strcmp(type, "cone") == 0)
		return (o_cone);
	else if (ft_strcmp(type, "plane") == 0)
		return (o_plane);
	return (0);
}

static void			*parse_material_json(t_key_value *obj_json, int type)
{

	// obj->object.= **(cl_float3 **)(array->value);
	return (0);
}

void				parse_objects_json(t_key_value *json, t_scene *scene)
{
	int				i;
	double			double_value;
	char			*str_value;
	t_array			*obj_array;
	t_key_value		*obj;
	t_array			*pos;
	union u_objects	object;

	i = -1;
	if (get_array(json, "figure", &obj_array) != 0)
		ft_error("Error get_array: figure");
	init_objects(&scene->object, obj_array->length);
	while (++i < obj_array->length)
	{
		if (getf_object_array(obj_array, i, &obj) != 0)
			ft_error("Error getf_object_array: obj");

		if (get_str(obj, "type", &str_value) != 0)
			ft_error("Error get_double: intensity");
		if ((scene->object[i].type = check_type(str_value)) == 0)
			ft_error("Error type object");
		if (scene->object[i].type == o_sphere)
		{
			parse_sphere_json(obj, &object.sphere);
			scene->object[i].object.sphere = object.sphere;
		}
		else if (scene->object[i].type == o_cylinder)
		{
			parse_cylinder_json(obj, &object.cylinder);
			scene->object[i].object.cylinder = object.cylinder;
		}
		else if (scene->object[i].type == o_cone)
		{
			parse_cone_json(obj, &object.cone);
			scene->object[i].object.cone = object.cone;
		}
		else if (scene->object[i].type == o_plane)
		{
			parse_plane_json(obj, &object.plane);
			scene->object[i].object.plane = object.plane;
		}
	}
	// printf("%d\n%d\n%d\n%d\n", scene->object[0].type, scene->object[1].type, scene->object[2].type, scene->object[3].type);
	scene->count_lights = obj_array->length;
}
