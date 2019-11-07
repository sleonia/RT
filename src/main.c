/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2019/11/04 01:12:02 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
			scene->view = matrix_on_vector(scene->cam->a, scene->cam->b, canvas_to_viewport(x, y, scene->view));
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
	rtv1->scene->cam->position = insert(0, 0, 0, rtv1->scene->cam->position);
	//разобраться с поворотом камеры

	rtv1->scene->view = (t_pos *)ft_memalloc(sizeof(t_pos));

	//инициализация света нужен прасер
	rtv1->scene->light = init_light(rtv1->scene->light);

	rtv1->scene->figure = (t_figure *)ft_memalloc(sizeof(t_figure));

	rtv1->scene->off = (t_light_off *)ft_memalloc(sizeof(t_light_off));

	//парсер чтобы считать сферы из файла в *shpere
	//инициальзация сфер
	rtv1->scene->figure->sphere = init_sphere(rtv1->scene->figure->sphere);

	trace_start(rtv1->sdl, rtv1->scene);
	return (0);
}
