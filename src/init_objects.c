#include "rtv1.h"


//t_object	*init_cylinder(t_object *obj, t_sphere_params *params)
//{
//	if (obj == NULL)
//	{
//		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
//			return (NULL);
//		obj->type = o_cylinder;
////		obj->objects.sphere = params.asdsadasdasdasda
//		return (obj);
//		//создать лист поместить в ноду объект вернуть лист;
//	}
//	else
//	{
//		t_object *new_obj;
//		new_obj->next = obj;
//		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
//			return NULL;
//		new_obj->type = o_cylinder;
////		obj->objects = params.asdasd
//		new_obj->next = obj;
//		return (new_obj);
//		return (obj);
//		// в текущий лист занести объект и тоже вернуть лист.
//	}
//}
//
//t_object	*init_cone(t_object *obj, t_cone_params *params)
//{
//	if (obj == NULL)
//	{
//		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
//			return (NULL);
//		obj->type = o_cone;
////		obj->objects.sphere = params.asdsadasdasdasda
//		return (obj);
//		//создать лист поместить в ноду объект вернуть лист;
//	}
//	else
//	{
//		t_object *new_obj;
//		new_obj->next = obj;
//		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
//			return NULL;
//		new_obj->type = o_cone;
////		obj->objects = params.asdasd
//		new_obj->next = obj;
//		return (new_obj);
//		// в текущий лист занести объект и тоже вернуть лист.
//	}
//}
//
//t_object	*init_planes(t_object *obj, t_planes_params *params)
//{
//	if (obj == NULL)
//	{
//		if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
//			return (NULL);
//		obj->type = o_plane;
////		obj->objects.sphere = params.asdsadasdasdasda
//		return (obj);
//		//создать лист поместить в ноду объект вернуть лист;
//	}
//	else
//	{
//		t_object *new_obj;
//		new_obj->next = obj;
//		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
//			return NULL;
//		new_obj->type = o_plane;
////		obj->objects = params.asdasd
//		new_obj->next = obj;
//		return (new_obj);
//		// в текущий лист занести объект и тоже вернуть лист.
//	}
//}

t_object	*init_spheres(t_object *obj, t_sphere_params params)
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
		//		obj->objects.sphere = params.asdsadasdasdasda
		return (obj);
		//создать лист поместить в ноду объект вернуть лист;
	}
	else
	{
		t_object *new_obj;
		if (!(new_obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return NULL;
		if (!(new_obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects))))
			return (NULL);
		new_obj->next = obj;
		new_obj->type = o_sphere;
		new_obj->color = params.color;
		new_obj->reflective = params.reflective;
		new_obj->specular = params.specular;
		new_obj->objects->sphere.center = params.pos;
		new_obj->objects->sphere.radius = params.radius;
		new_obj->next = obj;
		return (new_obj);
		// в текущий лист занести объект и тоже вернуть лист.
	}
}

t_object 	*init_scene(void)
{
	t_object *object;

	object = init_spheres(NULL,  (t_sphere_params){{0.0, -1.0, 3.0}, 1.0, 0xFF00FF, 500, 0.2});
	object = init_spheres(object,  (t_sphere_params){{2.0, 2.0, 3.0}, 1.0, 0xFF00FF, 500, 0.2});
	object = init_spheres(object,  (t_sphere_params){{-2.0, 2.0, 3.0}, 1.0, 0xFF00FF, 500, 0.2});
	return (object);
//	obj = init_spheres(obj)
//	init_spheres()
//	init_spheres()
//	init_spheres()
}

t_sphere	*init_sphere(t_sphere *sphere)
{
	t_sphere	*tmp;
	t_pos		*center1;
	t_pos		*center2;
	t_pos		*center3;
	t_pos		*center4;

	sphere = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center1 = (t_pos *)ft_memalloc(sizeof(t_pos));
	sphere->radius  = 1;
	sphere->color = 0xFF0000;
	sphere->center = insert(0, -1, 3, center1);
	sphere->specular = 500;
	sphere->reflective = 0.2;

/*	sphere->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center2 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = sphere->next;
	tmp->radius  = 1;
	tmp->color = 0x0000FF;
	tmp->center = insert(2, 0, 4, center2);
	tmp->specular = 500;
	tmp->reflective = 0.3;

	tmp->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->radius  = 1;
	tmp->color = 0x00FF00;
	tmp->center = insert(-2, 0, 4, center3);
	tmp->specular = 10;
	tmp->reflective = 0.4;

	tmp->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center4 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->radius  = 5000;
	tmp->color = 0xFFFF00;
	tmp->center = insert(0, -5001, 0, center4);
	tmp->specular = 1000;
	tmp->reflective = 0.5;*/
	return (sphere);
}