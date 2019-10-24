/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2019/10/24 12:57:08 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Решает квадратное уравнение и возвращает два корня если есть, если нет то INF
*/

t_result	*intersect_ray_sphere(t_result *res, t_cam *o, t_view *d, t_sphere *sphere)
{
	t_pos		oc;
	double		k1;
	double		k2;
	double		k3;


	oc = vector_minus(o->position, sphere->center);
	k1 = dot(d->position, d->position);
	k2 = 2 * dot(&oc, d->position);
	k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res->t1 = INFINITY;
		res->t2 = INFINITY;
		return (res);
	}
	res->t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res->t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
//	printf ("%f %f\n", res->t1, res->t2);
	return (res);
}

/*
** Находит ближайшую точку в позиции (x, y) среди всех сфер и закрашивает цветом
*/

int			trace_ray(t_cam *o, t_view *d, double t_min, double t_max, t_sphere *sphere, t_light *light)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_result	*res;
	t_sphere	*tmp;

	t_pos		*p;
	p = (t_pos *)ft_memalloc(sizeof(t_pos));
	t_pos		*n;
	n = (t_pos *)ft_memalloc(sizeof(t_pos));
	t_pos		buf;
	t_pos		*v;

	closest_t = INFINITY;
	closest_sphere = NULL;
	res = (t_result *)ft_memalloc(sizeof(t_result));
	tmp = sphere;
	while (tmp)
	{
		res = intersect_ray_sphere(res, o, d, tmp);
//		printf ("%f %f\n", res->t1, res->t2);
		if (res->t1 >= t_min && res->t1 <= t_max && res->t1 < closest_t)
		{
			closest_t = res->t1;
			closest_sphere = tmp;
		}
		else if (res->t2 >= t_min && res->t2 <= t_max && res->t2 < closest_t)
		{
			closest_t = res->t2;
			closest_sphere = tmp;
		}
		tmp = tmp->next;
	}
//	printf ("%f %f\n", res->t1, res->t2);
	free(res);
	if (closest_sphere == NULL) {
		free(p);
		free(n);
		return (BLACK);
	}
	///////////////
	buf = vector_on_number(d->position, closest_t);
	*p = vector_pus(o->position, &buf);
	*n = vector_minus(p, closest_sphere->center);
	*n = vector_div(n, vector_len(n));
	buf = vector_on_number(d->position, -1);
	double c = computer_lighting(p, n, &buf, closest_sphere->specular, light);
//	printf ("%f", c);
	int red = (closest_sphere->color & 0xFF0000) >> 16;
	red *= c;
	int green = (closest_sphere->color & 0x00FF00) >> 8;
	green *= c;
	int blue = (closest_sphere->color & 0x0000FF);
	blue *= c;
	free(p);
	free(n);
	return ((red << 16) | (green << 8) | blue);
}



/*
** 		Костыльное добавление сфер
**		НУЖЕН ПАРСЕР
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

	sphere->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center2 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = sphere->next;
	tmp->radius  = 1;
	tmp->color = 0x0000FF;
	tmp->center = insert(2, 0, 4, center2);
	tmp->specular = 500;

	tmp->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->radius  = 1;
	tmp->color = 0x00FF00;
	tmp->center = insert(-2, 0, 4, center3);
	tmp->specular = 10;

	tmp->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center4 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->radius  = 5000;
	tmp->color = 0xFFFF00;
	tmp->center = insert(0, -5002, 0, center4);
	tmp->specular = 1000;
	return (sphere);
}

int			main(void)
{
	t_cam		*o;
	t_view		*d;
	t_sphere	*sphere;
	int			x;
	int			y;
	int 		color;
	t_sdl		*sdl;
	t_light		*light;


	sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	sdl_init(sdl);

	//парсер чтобы считать сферы из файла в *shpere
	o = (t_cam *)ft_memalloc(sizeof(t_cam));
	o->position = (t_pos *)ft_memalloc(sizeof(t_pos));
	d = (t_view *)ft_memalloc(sizeof(t_view));
	d->position = (t_pos *)ft_memalloc(sizeof(t_pos));
//	d->position = (t_pos *)ft_memalloc(sizeof(t_pos));

	o->position = insert(0, 0, 0, o->position);
	x = -WIDTH / 2;
	sphere = NULL;
	sphere = init_sphere(sphere);
	light = NULL;
	light = init_light(light);
	while(x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while(y < HEIGHT / 2)
		{
			d->position = canvas_to_viewport(x, y, d->position);
//			printf("%f %f %f\n", d->position->x, d->position->y, d->position->z);
			color = trace_ray(o, d, 1.0, INFINITY, sphere, light);
			sdl->pixels = put_pixel(x, y, color, sdl);
			y++;
		}
		x++;
	}
	sdl_control(sdl);
	return (0);
}
