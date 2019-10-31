/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2019/10/31 16:17:06 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** 		Решает квадратное уравнение и возвращает два корня если есть, если нет то INF
*/

t_result	intersect_ray_sphere(t_pos *o, t_pos *d, t_sphere *sphere)
{
	t_pos		oc;
	double		k1;
	double		k2;
	double		k3;
	t_result	res;


	oc = vector_minus(o, sphere->center);
	k1 = dot(d, d);
	k2 = 2 * dot(&oc, d);
	k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
		return (res);
	}
	res.t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res.t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
//	printf ("%f %f\n", res->t1, res->t2);
	return (res);
}

/*
** 		Находит ближайшую точку в позиции (x, y) среди всех сфер и возвращает укзатель на сферу и ближайшую точку пересечения
*/

t_return	closest_intersection(t_pos *o, t_pos *d, double t_min, double t_max, t_sphere *sphere)
{
	t_result	res;
	t_sphere	*tmp;
	t_return	ret;

	ret.closest_t = INFINITY;
	ret.closest_sphere = NULL;
	tmp = sphere;
	while (tmp)
	{
		res = intersect_ray_sphere(o, d, tmp);
		if (res.t1 >= t_min && res.t1 <= t_max && res.t1 < ret.closest_t)
		{
			ret.closest_t = res.t1;
			ret.closest_sphere = tmp;
		}
		if (res.t2 >= t_min && res.t2 <= t_max && res.t2 < ret.closest_t)
		{
			ret.closest_t = res.t2;
			ret.closest_sphere = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

int 		color_scale(int	color, double c)
{
	int 	red;
	int 	green;
	int 	blue;

	red = (color & 0xFF0000) >> 16;
	red = (int)((double)red * c);
	green = (color & 0x00FF00) >> 8;
	green = (int)((double)green * c);
	blue = (color & 0x0000FF);
	blue = (int)((double)blue * c);
	return ((red << 16) | (green << 8) | blue);
}

t_pos		reflect_ray(t_pos *r, t_pos *n)
{
	t_pos	ret;
	t_pos	a;
	t_pos	b;

	a = vector_on_number(n, 2);
	b = vector_on_number(&a, dot(r, n));
	ret = vector_minus(&b, r);
	return (ret);
}

/*
** 		Находит ближайшую точку в позиции (x, y) среди всех сфер и возвращает цвет пикселя
*/

int			trace_ray(t_pos *o, t_pos *d, double t_min, double t_max, t_scene *scene, int depth)
{
	t_pos		p;
	t_pos		n;
	t_pos		buf;
	t_pos		r;
	t_return	ret;
	double 		c;
	int 		local_color;
	int 		reflected_color;
	double		ref;

	ret = closest_intersection(o, d, t_min, t_max, scene->figure->sphere);
	if (ret.closest_sphere == NULL)
		return (BLACK);

	//Часть для добавления бликов от света
	// 		Вычисление локального цвета
	buf = vector_on_number(d, ret.closest_t);
	p = vector_pus(o, &buf);
	n = vector_minus(&p, ret.closest_sphere->center);
	n = vector_div(&n, vector_len(&n));
	//Теперь buf это -D
	buf = vector_on_number(d, -1);
	// Вычисление коэфа для умножения на цвет сферы
	c = computer_lighting(&p, &n, &buf, ret.closest_sphere->specular, scene);
	local_color = color_scale(ret.closest_sphere->color, c);

	// Проверка выхода из рекурсии
	ref = ret.closest_sphere->reflective;
	if (depth <= 0 || ref <= 0)
		return (local_color);

	//Рекурсивная часть отражения объектов
	r = reflect_ray(&buf, &n);
	reflected_color = trace_ray(&p, &r, 0.001, INFINITY, scene, depth - 1);

	return (color_scale(local_color, 1 - ref) + color_scale(reflected_color, ref));

}

/*
** 		Костыльное добавление сфер
**		НУЖЕН ПАРСЕР
** 		массив структур вместо односвязного списка
**
*/

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
}

/*
**	Начало обхода по всем пикселям экрана
*/

int 		trace_start(t_sdl *sdl, t_scene *scene)
{
	int 	color;
	int 	x;
	int 	y;

	x = -WIDTH / 2;
	while(x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while(y < HEIGHT / 2)
		{
			scene->view = vector_on_vector(scene->cam->cam_rotation, canvas_to_viewport(x, y, scene->view), scene->view);
			color = trace_ray(scene->cam->position, scene->view, 1.0, INFINITY, scene, 3);
			sdl->pixels = put_pixel(x, y, color, sdl);
			y++;
		}
		x++;
	}
	sdl_control(sdl, scene);
	return (0);
}

int			main(void)
{
	t_rtv1		*rtv1;

	rtv1 = (t_rtv1 *)ft_memalloc(sizeof(t_rtv1));
	rtv1->sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	sdl_init(rtv1->sdl);

	rtv1->scene = (t_scene *)ft_memalloc(sizeof(t_scene));

	rtv1->scene->cam = (t_cam *)ft_memalloc(sizeof(t_cam));
	rtv1->scene->cam->position = (t_pos *)ft_memalloc(sizeof(t_pos));
	rtv1->scene->cam->cam_rotation = (t_pos *)ft_memalloc(sizeof(t_pos));
	rtv1->scene->cam->position = insert(0, 0, 0, rtv1->scene->cam->position);
	//разобраться с поворотом камеры
	rtv1->scene->cam->cam_rotation = insert(1, 1, 1, rtv1->scene->cam->cam_rotation);

	rtv1->scene->view = (t_pos *)ft_memalloc(sizeof(t_pos));

	//инициализация света нужен прасер
	rtv1->scene->light = init_light(rtv1->scene->light);

	rtv1->scene->figure = (t_figure *)ft_memalloc(sizeof(t_figure));

	//парсер чтобы считать сферы из файла в *shpere
	//инициальзация сфер
	rtv1->scene->figure->sphere = init_sphere(rtv1->scene->figure->sphere);

	trace_start(rtv1->sdl, rtv1->scene);
	return (0);
}
