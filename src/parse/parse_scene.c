/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:46:46 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 20:51:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam				*parse_cam_json(t_key_value *json, t_rt *rt)
{
	t_key_value		*cam;

	if (get_node(json, "camera", &cam) != 0)
		ft_error("get_node: camera");
	
	return (cam);
}
