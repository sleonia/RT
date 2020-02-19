/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:44:26 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 15:16:28 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				realloc_obj(SDL_Scancode scancode, t_scene *scene)
{
	int			i;
	int			count_objects;
	t_object	*object;

	i = -1;
	count_objects = scene->count_objects;
	scene->count_objects += 1;
	init_objects(&object, scene->count_objects);
	while (++i < count_objects)
		object[i] = scene->object[i];
	if (scancode == SDL_SCANCODE_KP_1)
		new_sphere(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_2)
		new_cylinder(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_3)
		new_cone(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_4)
		new_plane(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_5)
		new_parab(&object[i]);
	else if (scancode == SDL_SCANCODE_KP_6)
		new_torus(&object[i]);
	ft_memdel((void **)&scene->object);
	scene->object = object;
	return (0);
}
