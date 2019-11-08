/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:38:58 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 15:38:59 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cone_params(t_object *obj, t_cone_params params)
{
	obj->type = o_cone;
	obj->color = params.color;
	obj->reflective = params.reflective;
	obj->specular = params.specular;
	obj->objects->cone.center = params.pos;
	obj->objects->cone.radius = params.radius;
	obj->objects->cone.axis = params.axis;
	obj->objects->cone.axis = vector_normalize(&obj->objects->cone.axis);
}

void		init_plane_params(t_object *obj, t_plane_params params)
{
	obj->type = o_plane;
	obj->color = params.color;
	obj->reflective = params.reflective;
	obj->specular = params.specular;
	obj->objects->plane.center = params.pos;
	obj->objects->plane.normal = params.normal;
}

void		init_sphere_params(t_object *obj, t_sphere_params params)
{
	obj->type = o_sphere;
	obj->color = params.color;
	obj->reflective = params.reflective;
	obj->specular = params.specular;
	obj->objects->sphere.center = params.pos;
	obj->objects->sphere.radius = params.radius;
}

void		init_cylinder_params(t_object *obj, t_cylinder_params params)
{
	obj->type = o_cylinder;
	obj->color = params.color;
	obj->reflective = params.reflective;
	obj->specular = params.specular;
	obj->objects->cylinder.center = params.pos;
	obj->objects->cylinder.radius = params.radius;
	obj->objects->cylinder.axis = params.axis;
}
