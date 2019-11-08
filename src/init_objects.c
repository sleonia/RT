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

void		init_plane_params(t_object *obj, t_plane_params params)
{
	obj->type = o_plane;
	obj->color = params.color;
	obj->reflective = params.reflective;
	obj->specular = params.specular;
	obj->objects->plane.center = params.pos;
	obj->objects->plane.normal = params.normal;
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

void		init_sphere_params(t_object *obj, t_sphere_params params)
{
	obj->type = o_sphere;
	obj->color = params.color;
	obj->reflective = params.reflective;
	obj->specular = params.specular;
	obj->objects->sphere.center = params.pos;
	obj->objects->sphere.radius = params.radius;
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

void		init_scene(t_scene *scene)
{
	t_object	*object;
	t_light		*light;

	scene->cam->position = insert(0, 0, 0);
	light = NULL;
	light = init_lights(light, (t_light_params){'P', 0.2,
											 (t_pos){2.0, 2.0, 0.0}});
	light = init_lights(light, (t_light_params){'P', 0.2,
											 (t_pos){-2.0, 2.0, 0.0}});
	light = init_lights(light, (t_light_params){'D', 0.8,
											 (t_pos){2.0, 2.0, 1.0}});
	object = NULL;
	object = init_cylinder(object,  (t_cylinder_params){{-2.0, 0.0, 3.0},
													 {0, 1, 0}, 1.0,
													 0xFFFFFF, 500, 0.2});
	object = init_sphere(object,  (t_sphere_params){{0.0, -1.0, 3.0},
												 1.0, 0xFF00FF, 500,
												 0.2});
	object = init_sphere(object,  (t_sphere_params){{2.0, 2.0, 3.0},
												 1.0, 0xFF00FF, 500,
												 0.2});
	object = init_sphere(object,  (t_sphere_params){{-2.0, 2.0, 3.0},
												 1.0, 0xFF00FF, 500,
												 0.2});
	object = init_cone(object, (t_cone_params){{0.0, 0.0, 3.0},
											0.2, 0xFF0000, 500,
											0.2, {0.0, 1.0, 0.0}});
	object = init_plane(object,  (t_plane_params){{-2.0, 0.0, 3.0},
											   0xFFFFFF, 500, 0.2,
											   {0.0, 0.0, -1.0}});
	scene->object = object;
	scene->light = light;
}
