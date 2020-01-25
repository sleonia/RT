#include "rtv1.h"

void	find_camera(t_cam	**cam, t_key_value *tmp)
{
	t_key_value *node;
	int error;

	error = get_node(tmp, "camera", &node);
	*cam = (t_cam *)ft_memalloc(sizeof(t_cam));
	error = get_double(node, "angle_a", &(*cam)->a);
	error = get_double(node, "angle_b", &(*cam)->b);
	//error = get_array(node, "position", &(*cam)->position);
	
}

void	find_lights(t_light	**light, t_key_value *tmp)
{
	t_key_value *node;
	t_light		*new;
	char		*type;
	int error;

	//// создать т_лист, который бы хранил указатели на структуры нью
	//цикл?? while error != -2
	error = get_node(tmp, "light", &node);
	new = (t_light*)ft_memalloc(sizeof(t_light));
	error = get_str(node, "type", &type); 
	new->type = type[0];
	printf("%c", new->type);
	if (strcmp(&new->type, "p") == 0 || strcmp(&new->type,"d") == 0)
		printf("get_massive");
	error = get_double(node, "intensity", &new->intensity);
	printf("%f\n", new->intensity);
	if (light != NULL)
		new->next = *light;
	else
		new->next = NULL;
	*light = new;
}

void	find_spheres(t_object **object, t_key_value *tmp)
{
	t_key_value *node;
	t_key_value *node2;
	t_object	*new_obj;
	int error;
	// int		*pos;

	new_obj = (t_object *)ft_memalloc(sizeof(t_object));
	new_obj->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	error = get_node(tmp, "figure", &node);
	// error = get_node(node, "sphere_1", &node2);
	node2 = (t_key_value *)node->value[0];
	if (node2 != NULL)
	{
		// error = get_int(node2, "type", (int *)&new_obj->type);
		printf("\n%d\n", new_obj->type);
		// error = get_node(node2, "position", &node2);
		// pos = make_array(&node2);
		new_obj->objects->sphere.center = (t_pos){0, 0, 5};
		printf("%f %f %f\n", new_obj->objects->sphere.center.x, new_obj->objects->sphere.center.y, new_obj->objects->sphere.center.z);
		//error = get_arr(node2, "position", &new_obj->objects->sphere.center);
		error = get_double(node2, "radius_1", &new_obj->objects->sphere.radius);
		printf("%f", new_obj->objects->sphere.radius);
		//error = get_int(node2, "color", &new_obj->color);
		new_obj->color = 0xFF00FF;
		error = get_int(node2, "secular", &new_obj->specular);
		error = get_double(node2, "reflective", &new_obj->reflective);
		//массив для position
		if (object != NULL)
			new_obj->next = *object;
		else
			new_obj->next = NULL;
		*object = new_obj;
	}
	//new_obj = &object;
	//printf("%d",new_obj->objects->sphere.radius);
}

void	find_cone(t_object **object, t_key_value *tmp)
{
	//t_key_value *node;
	t_key_value *node2;
	t_object	*new_obj;
	int error;

	new_obj = (t_object *)ft_memalloc(sizeof(t_object));
	error = get_node(tmp, "sphere", &node2);
	if (node2 != NULL)
	{
		error = get_int(node2, "type", (int *)&new_obj->type);
		//error = get_arr(node2, "position", &new_obj->objects->cone.center);
		//error = get_arr(node2, "axis", &new_obj->objects->cone.axis);
		error = get_double(node2, "radius", &new_obj->objects->cone.radius);
		//error = get_int(node2, "color", &new_obj->color);
		error = get_int(node2, "secular", &new_obj->specular);
		error = get_double(node2, "reflective", &new_obj->reflective);
		if (object != NULL)
			new_obj->next = *object;
		else
			new_obj->next = NULL;
		*object = new_obj;
	}
}

void	find_cylinder(t_object **object, t_key_value *tmp)
{
	//t_key_value *node;
	t_key_value *node2;
	t_object	*new_obj;
	int error;

	new_obj = (t_object *)ft_memalloc(sizeof(t_object));
	error = get_node(tmp, "sphere", &node2);
	if (node2 != NULL)
	{
		error = get_int(node2, "type", (int *)&new_obj->type);
		//error = get_arr(node2, "position", &new_obj->objects->cylinder.center);
		//error = get_arr(node2, "axis", &new_obj->objects->cylinder.axis);
		error = get_double(node2, "radius", &new_obj->objects->cylinder.radius);
		//error = get_int(node2, "color", &new_obj->color);
		error = get_int(node2, "secular", &new_obj->specular);
		error = get_double(node2, "reflective", &new_obj->reflective);
		if (object != NULL)
			new_obj->next = *object;
		else
			new_obj->next = NULL;
		*object = new_obj;
	}
}

void	find_plane(t_object **object, t_key_value *tmp)
{
	//t_key_value *node;
	t_key_value *node2;
	t_object	*new_obj;
	int error;

	new_obj = (t_object *)ft_memalloc(sizeof(t_object));
	error = get_node(tmp, "sphere", &node2);
	if (node2 != NULL)
	{
		error = get_int(node2, "type", (int *)&new_obj->type);
		//error = get_arr(node2, "position", &new_obj->objects->plane.center);
		//error = get_arr(node2, "normal", &new_obj->objects->plane.axis);
		
		//error = get_int(node2, "color", &new_obj->color);
		error = get_int(node2, "secular", &new_obj->specular);
		error = get_double(node2, "reflective", &new_obj->reflective);
		if (object != NULL)
			new_obj->next = *object;
		else
			new_obj->next = NULL;
		*object = new_obj;
	}
}

void	find_all(t_scene *scene)
{
	t_key_value	*tmp;
	
	tmp = parse_json("test.json");
	scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	scene->light = NULL;
	find_camera(&scene->cam, tmp);
	printf("%f",scene->cam->a);
	find_lights(&scene->light, tmp);
	printf("%f", scene->light->intensity);
	find_spheres(&scene->object, tmp);
	// find_plane(&scene->object, tmp);
	// find_cylinder(&scene->object, tmp);
}