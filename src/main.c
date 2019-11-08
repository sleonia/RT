/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 17:38:06 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		trace_start(t_sdl *sdl, t_scene *scene)
{
	int	color;
	int	x;
	int	y;

	x = -WIDTH / 2;
	while (x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while (y < HEIGHT / 2)
		{
			scene->depth = 3;
			scene->view = matrix_on_vector(scene->cam->a,
					scene->cam->b, canvas_to_viewport(x, y, scene->view));
			*scene->view = vector_normalize(scene->view);
			color = trace_ray(&scene->cam->position, scene->view,
					(t_min_max){1.0, INFINITY}, scene);
			sdl->pixels = put_pixel(x, y, color, sdl);
			y++;
		}
		x++;
	}
	sdl_control(sdl, scene);
	return (0);
}

void	error_output(void)
{
	ft_putstr("input \"scene_1\" or \"scene_2\" ");
	ft_putendl("or \"scene_3\" or \"scene_4\"\n");
}

int		validate(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
	{
		error_output();
		return (0);
	}
	if (ft_strcmp(av[1], "scene_1") == 0)
		scene_1(scene);
	else if (ft_strcmp(av[1], "scene_2") == 0)
		scene_2(scene);
	else if (ft_strcmp(av[1], "scene_3") == 0)
		scene_3(scene);
	else if (ft_strcmp(av[1], "scene_4") == 0)
		scene_4(scene);
	else
	{
		error_output();
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_rtv1		*rtv1;

	rtv1 = (t_rtv1 *)ft_memalloc(sizeof(t_rtv1));
	rtv1->sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	sdl_init(rtv1->sdl);
	rtv1->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	rtv1->scene->cam = (t_cam *)ft_memalloc(sizeof(t_cam));
	rtv1->scene->view = (t_pos *)ft_memalloc(sizeof(t_pos));
	rtv1->scene->off = (t_light_off *)ft_memalloc(sizeof(t_light_off));
	if (!(validate(rtv1->scene, ac, av)))
		exit(0);
	trace_start(rtv1->sdl, rtv1->scene);
	return (0);
}
