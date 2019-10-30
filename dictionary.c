/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:04:07 by deladia           #+#    #+#             */
/*   Updated: 2019/10/30 16:04:10 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_dictionary	*dictionary(void)
{
	t_dictionary	*dict;

	dict = (t_dictionary *)ft_memalloc(sizeof(t_dictionary));
	dict->object[0] = "camera";
	dict->object[1] = "light";
	dict->object[2] = "figure";

	dict->camera_properties[0] = "position";
	dict->camera_properties[1] = "cam_rotation";

	dict->light_properties[0] = "type";
	dict->light_properties[1] = "intensity";
	dict->light_properties[2] = "position";

	dict->light_type[0] = "point";
	dict->light_type[1] = "ambient";
	dict->light_type[2] = "directional";

	dict->figure_type[0] = "sphere";
	dict->figure_type[1] = "cone";
	dict->figure_type[2] = "cylinder";
	dict->figure_type[3] = "plane";

	dict->figure_properties[0] = "radius";
	dict->figure_properties[1] = "color";
	dict->figure_properties[2] = "specular";
	dict->figure_properties[3] = "reflective";
	dict->figure_properties[4] = "position:";
	dict->figure_properties[5] = "height";

	dict->separator[0] = '{';
	dict->separator[1] = '}';
	dict->separator[2] = ',';
	dict->separator[3] = ':';
	dict->separator[4] = '"';
	return (dict);
}