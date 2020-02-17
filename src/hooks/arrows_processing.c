/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 05:16:30 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 11:08:12 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	down_arrow(t_object *hi_lited_object)
{
	if (hi_lited_object->type == o_sphere)
		hi_lited_object->object.sphere.center.v4[1] -= 0.17;
	if (hi_lited_object->type == o_cylinder)
		hi_lited_object->object.cylinder.center.v4[1] -= 0.17;
	if (hi_lited_object->type == o_cone)
		hi_lited_object->object.cone.center.v4[1] -= 0.17;
	if (hi_lited_object->type == o_parab)
		hi_lited_object->object.parab.center.v4[1] -= 0.17;
	if (hi_lited_object->type == o_torus)
		hi_lited_object->object.parab.center.v4[1] -= 0.17;
}

static void	up_arrow(t_object *hi_lited_object)
{
	if (hi_lited_object->type == o_sphere)
		hi_lited_object->object.sphere.center.v4[1] += 0.17;
	if (hi_lited_object->type == o_cylinder)
		hi_lited_object->object.cylinder.center.v4[1] += 0.17;
	if (hi_lited_object->type == o_cone)
		hi_lited_object->object.cone.center.v4[1] += 0.17;
	if (hi_lited_object->type == o_parab)
		hi_lited_object->object.parab.center.v4[1] += 0.17;
	if (hi_lited_object->type == o_torus)
		hi_lited_object->object.parab.center.v4[1] += 0.17;
}

static void	left_arrow(t_object *hi_lited_object)
{
	if (hi_lited_object->type == o_sphere)
		hi_lited_object->object.sphere.center.v4[0] -= 0.17;
	if (hi_lited_object->type == o_cylinder)
		hi_lited_object->object.cylinder.center.v4[0] -= 0.17;
	if (hi_lited_object->type == o_cone)
		hi_lited_object->object.cone.center.v4[0] -= 0.17;
	if (hi_lited_object->type == o_parab)
		hi_lited_object->object.parab.center.v4[0] -= 0.17;
	if (hi_lited_object->type == o_torus)
		hi_lited_object->object.parab.center.v4[0] -= 0.17;
}

static void	right_arrow(t_object *hi_lited_object)
{
	if (hi_lited_object->type == o_sphere)
		hi_lited_object->object.sphere.center.v4[0] += 0.17;
	if (hi_lited_object->type == o_cylinder)
		hi_lited_object->object.cylinder.center.v4[0] += 0.17;
	if (hi_lited_object->type == o_cone)
		hi_lited_object->object.cone.center.v4[0] += 0.17;
	if (hi_lited_object->type == o_parab)
		hi_lited_object->object.parab.center.v4[0] += 0.17;
	if (hi_lited_object->type == o_torus)
		hi_lited_object->object.parab.center.v4[0] += 0.17;
}

void		arrows_processing(SDL_Scancode scancode, t_object *hi_lited_object)
{
	if (!hi_lited_object)
		return ;
	if (scancode == SDL_SCANCODE_DOWN)
		down_arrow(hi_lited_object);
	if (scancode == SDL_SCANCODE_UP)
		up_arrow(hi_lited_object);
	if (scancode == SDL_SCANCODE_LEFT)
		left_arrow(hi_lited_object);
	if (scancode == SDL_SCANCODE_RIGHT)
		right_arrow(hi_lited_object);
}
