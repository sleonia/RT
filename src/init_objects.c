#include "rtv1.h"


t_object	*init_cone(t_object *obj, t_cone_params params)
{
	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		obj->type = o_cone;
		obj->color = params.color;
		obj->reflective = params.reflective;
		obj->specular = params.specular;
		obj->objects->cone.center = params.pos;
		obj->objects->cone.radius = params.radius;
		obj->objects->cone.axis = params.axis;
		obj->objects->cone.axis = vector_normalize(&obj->objects->cone.axis);
		return (obj);
	}
	else
	{
		t_object *new_obj;
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return NULL;
		if (!(new_obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		new_obj->type = o_cone;
		new_obj->color = params.color;
		new_obj->reflective = params.reflective;
		new_obj->specular = params.specular;
		new_obj->objects->cone.center = params.pos;
		new_obj->objects->cone.radius = params.radius;
		new_obj->objects->cone.axis = params.axis;
		obj->objects->cone.axis = vector_normalize(&obj->objects->cone.axis);
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object	*init_plane(t_object *obj, t_plane_params params)
{
	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		obj->type = o_plane;
		obj->color = params.color;
		obj->reflective = params.reflective;
		obj->specular = params.specular;
		obj->objects->plane.center = params.pos;
		obj->objects->plane.normal = params.normal;
		return (obj);
	}
	else
	{
		t_object *new_obj;
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return NULL;
		if (!(new_obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		new_obj->type = o_plane;
		new_obj->color = params.color;
		new_obj->reflective = params.reflective;
		new_obj->specular = params.specular;
		new_obj->objects->plane.center = params.pos;
		new_obj->objects->plane.normal = params.normal;
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object	*init_sphere(t_object *obj, t_sphere_params params)
{
	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		obj->type = o_sphere;
		obj->color = params.color;
		obj->reflective = params.reflective;
		obj->specular = params.specular;
		obj->objects->sphere.center = params.pos;
		obj->objects->sphere.radius = params.radius;
		return (obj);
	}
	else
	{
		t_object *new_obj;
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return NULL;
		if (!(new_obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		new_obj->type = o_sphere;
		new_obj->color = params.color;
		new_obj->reflective = params.reflective;
		new_obj->specular = params.specular;
		new_obj->objects->sphere.center = params.pos;
		new_obj->objects->sphere.radius = params.radius;
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object	*init_cylinder(t_object *obj, t_cylinder_params params)
{
	if (obj == NULL)
	{
		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (NULL);
		if (!(obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		obj->type = o_cylinder;
		obj->color = params.color;
		obj->reflective = params.reflective;
		obj->specular = params.specular;
		obj->objects->cylinder.center = params.pos;
		obj->objects->cylinder.radius = params.radius;
		obj->objects->cylinder.axis = params.axis;
		return (obj);
	}
	else
	{
		t_object *new_obj;
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return NULL;
		if (!(new_obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		obj->type = o_cylinder;
		obj->color = params.color;
		obj->reflective = params.reflective;
		obj->specular = params.specular;
		obj->objects->cylinder.center = params.pos;
		obj->objects->cylinder.radius = params.radius;
		obj->objects->cylinder.axis = params.axis;
		new_obj->next = obj;
		return (new_obj);
	}
}

t_object 	*init_scene(void)
{
	t_object *object;

	object = NULL;
	object = init_cylinder(object,  (t_cylinder_params){{-2.0, 0.0, 3.0}, {0, 1, 0}, 1.0, 0xFFFFFF, 500, 0.2});
	object = init_sphere(object,  (t_sphere_params){{0.0, -1.0, 3.0}, 1.0, 0xFF00FF, 500, 0.2});
	object = init_sphere(object,  (t_sphere_params){{2.0, 2.0, 3.0}, 1.0, 0xFF00FF, 500, 0.2});
	object = init_sphere(object,  (t_sphere_params){{-2.0, 2.0, 3.0}, 1.0, 0xFF00FF, 500, 0.2});
	object = init_cone(object, (t_cone_params){{-2.0, 2.0, 3.0}, 0.2, 0xFFFFFF, 500, 0.2, {1.0, 0.0, 0.0}});
	object = init_plane(object,  (t_plane_params){{-2.0, 0.0, 3.0}, 0xFFFFFF, 500, 0.2, {0.0, 0.0, -1.0}});
//	object
	return (object);
}
