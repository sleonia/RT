/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2019/12/09 20:37:17 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// t_return	closest_intersection(t_pos *o, t_pos *d, double t_min, double t_max, t_object **obj)
// {
// 	t_result	res;
// 	t_object	**tmp;
// 	t_return	ret;
// 	int 		i;

// 	ret.closest_t = INFINITY;
// 	ret.closest_object = NULL;
// 	tmp = obj;
// 	i = 0;
// 	while (i < 7)
// 	{
// 		res = get_intersect(o, d, tmp[i]);
// 		if (res.t1 >= t_min && res.t1 <= t_max && res.t1 < ret.closest_t)
// 		{
// 			ret.closest_t = res.t1;
// 			ret.closest_object = tmp[i];
// 		}
// 		if (res.t2 >= t_min && res.t2 <= t_max && res.t2 < ret.closest_t)
// 		{
// 			ret.closest_t = res.t2;
// 			ret.closest_object = tmp[i];
// 		}
// //		tmp = tmp->next;
// 		i++;
// 	}
// 	return (ret);
// }

// int 		color_scale(int	color, double c)
// {
// 	int 	red;
// 	int 	green;
// 	int 	blue;

// 	red = (color & 0xFF0000) >> 16;
// 	red = (int)((double)red * c);
// 	green = (color & 0x00FF00) >> 8;
// 	green = (int)((double)green * c);
// 	blue = (color & 0x0000FF);
// 	blue = (int)((double)blue * c);
// 	return ((red << 16) | (green << 8) | blue);
// }

// t_pos		reflect_ray(t_pos *r, t_pos *n)
// {
// 	t_pos	ret;
// 	t_pos	a;
// 	t_pos	b;

// 	a = vector_on_number(n, 2);
// 	b = vector_on_number(&a, ft_dot(r, n));
// 	ret = vector_minus(&b, r);
// 	return (ret);
// }

/*
** 		Находит ближайшую точку в позиции (x, y) среди всех сфер и возвращает цвет пикселя
*/

// int			 trace_ray(t_pos *o, t_pos *d, double t_min, double t_max, t_scene *scene, int depth)
// {
// 	t_pos p;
// 	t_pos n;
// 	t_pos buf;
// 	t_pos r;
// 	t_return ret;
// 	double c;
// 	int local_color;
// 	int reflected_color;
// 	double ref;

// 	ret = closest_intersection(o, d, t_min, t_max, scene->object);
// 	if (ret.closest_object == NULL)
// 		return (BLACK);
// //	return (ret.closest_sphere->color);
// 	//Часть для добавления бликов от света
// 	// 		Вычисление локального цвета
// 	buf = vector_on_number(d, ret.closest_t);
// 	p = vector_pus(o, &buf);
// //	n = vector_minus(&p, &ret.closest_object->center);
// 	n = get_obj_normal(&p, &ret, o, d);
// 	n = vector_div(&n, vector_len(&n));
// 	//Теперь buf это -D
// 	buf = vector_on_number(d, -1);
// 	// Вычисление коэфа для умножения на цвет сферы
// 	c = computer_lighting(&p, &n, &buf, ret.closest_object->specular, scene);
// 	local_color = color_scale(ret.closest_object->color, c);

// 	// Проверка выхода из рекурсии
// 	ref = ret.closest_object->reflective;
// 	if (depth <= 0 || ref <= 0 || scene->off->reflect)
// 		return (local_color);

// 	//Рекурсивная часть отражения объектов
// 	r = reflect_ray(&buf, &n);
// 	reflected_color = trace_ray(&p, &r, 0.001, INFINITY, scene, depth - 1);
// 	return (color_scale(local_color, 1 - ref) + color_scale(reflected_color, ref));
// }
/*
** 		Костыльное добавление сфер
**		НУЖЕН ПАРСЕР
** 		массив структур вместо односвязного списка
**
*/

/*t_sphere	*init_sphere(t_sphere *sphere)
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

	sphere->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
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
	tmp->reflective = 0.5;
	return (sphere);
}*/

/*
**	Начало обхода по всем пикселям экрана
*/

// int 		trace_start(t_sdl *sdl, t_scene *scene)
// {
// 	int 	color;
// 	int 	x;
// 	int 	y;

// 	x = -WIDTH / 2;
// 	while(x < WIDTH / 2)
// 	{
// 		y = -HEIGHT / 2;
// 		while(y < HEIGHT / 2)
// 		{
// 			scene->view = matrix_on_vector(scene->cam->a, scene->cam->b, canvas_to_viewport(x, y, scene->view));
// 			color = trace_ray(&scene->cam->position, scene->view, 1.0, INFINITY, scene, 3);
// 			sdl->pixels = put_pixel(x, y, color, sdl);
// 			y++;
// 		}
// 		x++;
// 	}
// 	sdl_control(sdl, scene);
// 	return (0);
// }



void		init_plane_param(t_object *obj, t_plane_params params)
{
	(*obj).type = o_plane;
	(*obj).color = params.color;
	(*obj).reflective = params.reflective;
	(*obj).specular = params.specular;
	(*obj).center = params.pos;
	(*obj).normal = params.normal;
}

// void		init_cylinder_param(t_object *obj, t_cylinder_params params)
// {
// 	double	len;
	
// 	obj->type = o_cylinder;
// 	obj->color = params.color;
// 	obj->reflective = params.reflective;
// 	obj->specular = params.specular;
// 	obj->objects->cylinder.center = params.pos;
// 	len = vector_len(&params.axis);
// 	if (len == 1)
// 	 	obj->objects->cylinder.axis = params.axis;
// 	else if (len != 0)
// 	{
// 		obj->objects->cylinder.axis.x = params.axis.x / len;
// 		obj->objects->cylinder.axis.y = params.axis.y / len;
// 		obj->objects->cylinder.axis.z = params.axis.z / len;
// 	}
// 	obj->objects->cylinder.radius = params.radius;
// }

// void		init_cone_param(t_object *obj, t_cone_params params)
// {
// 	double	len;
	
// 	obj->type = o_cone;
// 	obj->color = params.color;
// 	obj->reflective = params.reflective;
// 	obj->specular = params.specular;
// 	obj->objects->cone.center = params.pos;
// 	len = vector_len(&params.axis);
// 	if (len == 1)
// 	 	obj->objects->cylinder.axis = params.axis;
// 	else if (len != 0)
// 	{
// 		obj->objects->cylinder.axis.x = params.axis.x / len;
// 		obj->objects->cylinder.axis.y = params.axis.y / len;
// 		obj->objects->cylinder.axis.z = params.axis.z / len;
// 	}
// 	obj->objects->cone.tan = params.tan;
// }

void		init_sphere_param(t_object obj, t_sphere_params params)
{
	obj.type = o_sphere;
	obj.color = params.color;
	obj.reflective = params.reflective;
	obj.specular = params.specular;
	obj.center = params.pos;
	obj.radius = params.radius;
}

void	init_object(t_object **object)
{
	*object = (t_object *)ft_memalloc(sizeof(t_object) * 4);

	// object[4] = (t_object *)ft_memalloc(sizeof(t_object));
	// object[5] = (t_object *)ft_memalloc(sizeof(t_object));
	// object[6] = (t_object *)ft_memalloc(sizeof(t_object));
	
	// (*object)[0].objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	// (*object)[1].objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	// (*object)[2].objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	// (*object)[3].objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	// object[4]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	// object[5]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	// object[6]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
	(*object)[0].type = o_sphere;
	(*object)[0].color = 0xFF0000;
	(*object)[0].reflective = 0.2f;
	(*object)[0].specular = 500;
	(*object)[0].center = (cl_float3){0, -1, 3};
	(*object)[0].radius = 1.0f;

	(*object)[1].type = o_sphere;
	(*object)[1].color = 0x0000FF;
	(*object)[1].reflective = 0.3f;
	(*object)[1].specular = 500;
	(*object)[1].center = (cl_float3){2, 0, 4};
	(*object)[1].radius = 1.0f;

	(*object)[2].type = o_sphere;
	(*object)[2].color = 0x00FF00;
	(*object)[2].reflective = 0.4f;
	(*object)[2].specular = 300;
	(*object)[2].center = (cl_float3){-2, 0, 4};
	(*object)[2].radius = 1.0f;

	(*object)[3].type = o_sphere;
	(*object)[3].color = 0xFFFF00;
	(*object)[3].reflective = 0.4f;
	(*object)[3].specular = 300;
	(*object)[3].center = (cl_float3){0, -5001, 0};
	(*object)[3].radius = 5000.0f;
	// init_sphere_param((*object)[0], (t_sphere_params){(cl_float3){0, -1, 3}, 1.0f, 0xFF0000, 500, 0.2f});
	// init_sphere_param((*object)[1], (t_sphere_params){(cl_float3){2, 0, 4}, 1.0f, 0x0000FF, 500, 0.3f});
	// init_sphere_param((*object)[2], (t_sphere_params){(cl_float3){-2, 0, 4}, 1.0f, 0x00FF00, 10, 0.4f});
	// init_sphere_param((*object)[3], (t_sphere_params){(cl_float3){0, -5001, 0}, 5000.0f, 0xFFFF00, 1000, 0.5f});
	// init_plane_param(object[4], (t_plane_params){{0, 0, 26}, 0x0000FF, 500, 0.4, {0, 0, 1}});
	// init_cylinder_param(object[5], (t_cylinder_params){{0, 2, 5},{1, 0.5, 0}, 0.1, 0xFFFFF0, 500, 0.4});
	// init_cone_param(object[6], (t_cone_params){{0, 3, 5},{0, 1, 0}, 0.2, 0xFF00FF, 500, 0.4});
}

// t_object	**init_object_1(void)
// {
// 	t_object	**object;

// 	object = (t_object **)ft_memalloc(sizeof(t_object *) * 7);
// 	object[0] = (t_object *)ft_memalloc(sizeof(t_object));
// 	object[1] = (t_object *)ft_memalloc(sizeof(t_object));
// 	object[2] = (t_object *)ft_memalloc(sizeof(t_object));
// 	object[3] = (t_object *)ft_memalloc(sizeof(t_object));
// 	object[4] = (t_object *)ft_memalloc(sizeof(t_object));
// 	object[5] = (t_object *)ft_memalloc(sizeof(t_object));
// 	object[6] = (t_object *)ft_memalloc(sizeof(t_object));
	
// 	object[0]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	object[1]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	object[2]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	object[3]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	object[4]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	object[5]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	object[6]->objects = (union u_objects *)ft_memalloc(sizeof(union u_objects));
// 	init_sphere_param(object[0], (t_sphere_params){{0, -1, 3}, 1.0, 0xFF0000, 500, 0.2});
// 	init_sphere_param(object[1], (t_sphere_params){{2, 0, 4}, 1.0, 0x0000FF, 500, 0.3});
// 	init_sphere_param(object[2], (t_sphere_params){{-2, 0, 4}, 1.0, 0x00FF00, 10, 0.4});
// 	init_sphere_param(object[3], (t_sphere_params){{0, -5001, 0}, 5000.0, 0xFFFF00, 1000, 0.5});
// 	init_plane_param(object[4], (t_plane_params){{0, 0, 26}, 0x0000FF, 500, 0.4, {0, 0, 1}});
// 	init_cylinder_param(object[5], (t_cylinder_params){{0, 2, 5},{1, 0.5, 0}, 0.1, 0xFFFFF0, 500, 0.4});
// 	init_cone_param(object[6], (t_cone_params){{0, 3, 5},{0, 1, 0}, 0.2, 0xFF00FF, 500, 0.4});
// 	return (object);
// }

int			main(void)
{
	t_rtv1		*rtv1;

	rtv1 = (t_rtv1 *)ft_memalloc(sizeof(t_rtv1));
	rtv1->sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	sdl_init(rtv1->sdl);

	rtv1->scene = (t_scene *)ft_memalloc(sizeof(t_scene));

	rtv1->scene->cam = (t_cam *)ft_memalloc(sizeof(t_cam));
	
	rtv1->scene->cam->pos = (cl_float3){0.0, 2.0, 0.0};

	//разобраться с поворотом камеры

	// rtv1->scene->view = (t_pos *)ft_memalloc(sizeof(t_pos));

	//инициализация света нужен прасер
	// rtv1->scene->light = init_light();

//	rtv1->scene->figure = (t_figure *)ft_memalloc(sizeof(t_figure));

	rtv1->scene->off = (t_light_off *)ft_memalloc(sizeof(t_light_off));

	//парсер чтобы считать сферы из файла в *shpere
	//инициальзация сфер
//	rtv1->scene->figure->sphere = init_sphere(rtv1->scene->figure->sphere);
	// rtv1->scene->object = init_object();
	init_object(&rtv1->scene->object);
	init_light(&rtv1->scene->light);
	
	// printf("%f ", rtv1->scene->object[0].reflective);
	// printf("%f ", rtv1->scene->object[1].reflective);
	// printf("%f ", rtv1->scene->object[2].reflective);
	// trace_start(rtv1->sdl, rtv1->scene);
	rtv1->opencl = (t_cl *)ft_memalloc(sizeof(t_cl));
	read_kernel(rtv1->opencl);
	create_cl(rtv1->opencl, rtv1->sdl, rtv1->scene);
	// printf("%f ", rtv1->scene->light[0]->intensity);
	// int i = 0;
	// while (i < HEIGHT * WIDTH)
	// {
	// 	printf("%d ", rtv1->sdl->pixels[i]);
	// 	i++;
	// }
	sdl_control(rtv1->sdl, rtv1->scene);
	return (0);
}
//написать функцию которая вызывает vector_on_number миллион раз и посмотреть время, а потом
//отправляю с * принимаю без
//отправляю без принимаю с *
