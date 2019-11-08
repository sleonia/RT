/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:42:32 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 15:42:33 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_light		*light_in(void)
{
	t_light *light;

	light = NULL;
	light = init_lights(light, (t_light_params){'P', 0.2,
												(t_pos){2.0, 2.0, 0.0}});
	light = init_lights(light, (t_light_params){'P', 0.2,
												(t_pos){-2.0, 2.0, 0.0}});
	light = init_lights(light, (t_light_params){'D', 0.8,
												(t_pos){2.0, 2.0, 1.0}});
	return (light);
}

static t_object		*object_in(void)
{
	t_object *object;

	object = NULL;
	object = init_cylinder(object, (t_cylinder_params){{-2.0, 0.0, 3.0},
														{0, 1, 0}, 1.0,
														0xFFFFFF, 500, 0.2});
	object = init_sphere(object, (t_sphere_params){{2.0, 2.0, 3.0},
													1.0, 0xFF00FF, 500,
													0.2});
	object = init_sphere(object, (t_sphere_params){{-2.0, 2.0, 3.0},
												1.5, 0xFF00FF, 500,
												0.2});
	object = init_cone(object, (t_cone_params){{0.0, 0.0, 3.0},
											0.2, 0xFF0000, 500,
											0.2, {0.0, 1.0, 0.0}});
	object = init_plane(object, (t_plane_params){{-2.0, 0.0, 3.0},
											0xFFFFFF, 500, 0.2,
											{0.0, 0.0, -1.0}});
	return (object);
}

void				scene_1(t_scene *scene)
{
	t_object	*object;
	t_light		*light;

	scene->cam->position = insert(0, 0, -5);
	light = light_in();
	object = object_in();
	scene->object = object;
	scene->light = light;
}
