/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:55:25 by deladia           #+#    #+#             */
/*   Updated: 2020/01/17 19:56:02 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		scene_2(t_scene *scene)
{
	t_object	*object;
	t_light		*light;

	object = NULL;
	light = NULL;
	light = init_lights(light, (t_light_params){'P', 0.8,
		(t_pos){2.0, 2.0, 0.0}});
	object = init_sphere(object, (t_sphere_params){{0.0, 0.0, 3.0},
		1.0, 0xFF00F0, 100, 0.2});
	scene->object = object;
	scene->light = light;
}
