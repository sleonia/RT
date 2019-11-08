/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:37:29 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 15:37:31 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	*init_cone(t_object *obj, t_cone_params params)
{
	t_object *new_obj;

	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_cone_params(obj, params);
		return (obj);
	}
	else
	{
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(new_obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_cone_params(new_obj, params);
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object	*init_plane(t_object *obj, t_plane_params params)
{
	t_object *new_obj;

	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_plane_params(obj, params);
		return (obj);
	}
	else
	{
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(new_obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_plane_params(new_obj, params);
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object	*init_sphere(t_object *obj, t_sphere_params params)
{
	t_object *new_obj;

	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_sphere_params(obj, params);
		return (obj);
	}
	else
	{
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(new_obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_sphere_params(new_obj, params);
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object	*init_cylinder(t_object *obj, t_cylinder_params params)
{
	t_object *new_obj;

	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_cylinder_params(obj, params);
		return (obj);
	}
	else
	{
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(new_obj->objects = (union u_objects *)
				ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		init_cylinder_params(new_obj, params);
		new_obj->next = obj;
		return (new_obj);
	}
}

t_light		*init_lights(t_light *l, t_light_params params)
{
	t_light *new_light;

	if (l == NULL)
	{
		if (!(l = (t_light *)ft_memalloc(sizeof(t_light))))
			return (NULL);
		l->type = params.type;
		l->intensity = params.intensity;
		l->position = params.pos;
		return (l);
	}
	else
	{
		if (!(new_light = (t_light *)ft_memalloc(sizeof(t_light))))
			return (NULL);
		new_light->type = params.type;
		new_light->intensity = params.intensity;
		new_light->position = params.pos;
		new_light->next = l;
		return (new_light);
	}
}
