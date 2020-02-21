/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 05:16:30 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 12:23:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	down_arrow(t_object *select_obj)
{
	if (select_obj->type == o_sphere)
		select_obj->object.sphere.center.v4[1] -= 0.17;
	if (select_obj->type == o_cylinder)
		select_obj->object.cylinder.center.v4[1] -= 0.17;
	if (select_obj->type == o_cone)
		select_obj->object.cone.center.v4[1] -= 0.17;
	if (select_obj->type == o_parab)
		select_obj->object.parab.center.v4[1] -= 0.17;
	if (select_obj->type == o_torus)
		select_obj->object.parab.center.v4[1] -= 0.17;
}

static void	up_arrow(t_object *select_obj)
{
	if (select_obj->type == o_sphere)
		select_obj->object.sphere.center.v4[1] += 0.17;
	if (select_obj->type == o_cylinder)
		select_obj->object.cylinder.center.v4[1] += 0.17;
	if (select_obj->type == o_cone)
		select_obj->object.cone.center.v4[1] += 0.17;
	if (select_obj->type == o_parab)
		select_obj->object.parab.center.v4[1] += 0.17;
	if (select_obj->type == o_torus)
		select_obj->object.parab.center.v4[1] += 0.17;
}

static void	left_arrow(t_object *select_obj)
{
	if (select_obj->type == o_sphere)
		select_obj->object.sphere.center.v4[0] -= 0.17;
	if (select_obj->type == o_cylinder)
		select_obj->object.cylinder.center.v4[0] -= 0.17;
	if (select_obj->type == o_cone)
		select_obj->object.cone.center.v4[0] -= 0.17;
	if (select_obj->type == o_parab)
		select_obj->object.parab.center.v4[0] -= 0.17;
	if (select_obj->type == o_torus)
		select_obj->object.parab.center.v4[0] -= 0.17;
}

static void	right_arrow(t_object *select_obj)
{
	if (select_obj->type == o_sphere)
		select_obj->object.sphere.center.v4[0] += 0.17;
	if (select_obj->type == o_cylinder)
		select_obj->object.cylinder.center.v4[0] += 0.17;
	if (select_obj->type == o_cone)
		select_obj->object.cone.center.v4[0] += 0.17;
	if (select_obj->type == o_parab)
		select_obj->object.parab.center.v4[0] += 0.17;
	if (select_obj->type == o_torus)
		select_obj->object.parab.center.v4[0] += 0.17;
}

void		arrows_processing(SDL_Scancode scancode, t_object *select_obj)
{
	if (!select_obj)
		return ;
	if (scancode == SDL_SCANCODE_DOWN)
		down_arrow(select_obj);
	if (scancode == SDL_SCANCODE_UP)
		up_arrow(select_obj);
	if (scancode == SDL_SCANCODE_LEFT)
		left_arrow(select_obj);
	if (scancode == SDL_SCANCODE_RIGHT)
		right_arrow(select_obj);
}
