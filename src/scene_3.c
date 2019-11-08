/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:38:20 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 17:38:22 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_light		*light_in(void)
{
	t_light *light;

	light = NULL;
	light = init_lights(light, (t_light_params){'P', 0.8,
												(t_pos){0.0, 0.0, 0.0}});
	return (light);
}

static t_object		*object_in(void)
{
	t_object *object;

	object = NULL;
	object = init_cylinder(object, (t_cylinder_params){{0.0, 0.0, 3.0},
													{-1, 1, 0}, 1.5,
													0xFFFFFF, 500, 0.2});
	object = init_cylinder(object, (t_cylinder_params){{0.0, 0.0, 3.0},
													{1, 1, 0}, 1.5,
													0xFFFFFF, 500, 0.2});
	return (object);
}

void				scene_3(t_scene *scene)
{
	t_object	*object;
	t_light		*light;

	scene->cam->position = insert(0, 0, -10);
	light = light_in();
	object = object_in();
	scene->object = object;
	scene->light = light;
}
