/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/01/27 05:28:35 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

void	init_object(t_object **object)
{
	*object = (t_object *)ft_memalloc(sizeof(t_object) * 6);

	(*object)[0].type = o_sphere;
	(*object)[0].material.color = (cl_float3){1, 0, 0};
	(*object)[0].material.reflection = 0.5f; // от 0.1 до 1.0
	(*object)[0].material.refraction = 0.0f; // от 1.0 до 1.3
	(*object)[0].material.sp_ex = 50.0f;
	(*object)[0].material.al = (cl_float2){1.0, 1.0};
	(*object)[0].object.sphere.center = (cl_float3){0.0, -2.0, 3};
	(*object)[0].object.sphere.radius = 3.0f;

	(*object)[1].type = o_sphere;
	(*object)[1].material.color = (cl_float3){0, 1, 0};
	(*object)[1].material.reflection = 0.5f;
	(*object)[1].material.refraction = 0.0f;
	(*object)[1].material.sp_ex = 50.0f;
	(*object)[1].material.al = (cl_float2){1.0, 1.0};
	(*object)[1].object.sphere.center = (cl_float3){4, 0, 8};
	(*object)[1].object.sphere.radius = 3.0f;

	(*object)[2].type = o_sphere;
	(*object)[2].material.color = (cl_float3){0, 0, 1};
	(*object)[2].material.reflection = 0.5f;
	(*object)[2].material.refraction = 0.0f;
	(*object)[2].material.sp_ex = 50.0f;
	(*object)[2].material.al = (cl_float2){1.0, 1.0};
	(*object)[2].object.sphere.center = (cl_float3){-4, 0, 8};
	(*object)[2].object.sphere.radius = 3.0f;

	// (*object)[3].type = o_plane;
	// (*object)[3].material.color = (cl_float3){1, 0, 1};
	// (*object)[3].material.reflection = 0.9f;
	// (*object)[3].material.refraction = 0.f;
	// (*object)[3].material.sp_ex = 10.0f;
	// (*object)[3].material.al = (cl_float2){1.0, 0.0};
	// (*object)[3].object.plane.axis = (cl_float3){0, 0, 1};
	// (*object)[3].object.plane.dist = 8;

	// (*object)[4].type = o_cone;
	// (*object)[4].material.color = (cl_float3){1, 0, 1};
	// (*object)[4].material.reflection = 0.9f;
	// (*object)[4].material.refraction = 0.f;
	// (*object)[4].material.sp_ex = 50.0f;
	// (*object)[4].material.al = (cl_float2){1.0, 0.4};
	// (*object)[4].object.cone.center = (cl_float3){0, 0, 5};
	// (*object)[4].object.cone.axis = (cl_float3){0, 1, 0};
	// (*object)[4].object.cone.length = 10.0f;
	// (*object)[4].object.cone.tan = 0.25;

	// (*object)[5].type = o_cylinder;
	// (*object)[5].material.color = (cl_float3){1, 1, 0};
	// (*object)[5].material.refraction = 0.0f;
	// (*object)[5].material.reflection = 0.9f;
	// (*object)[5].material.sp_ex = 50.0f;
	// (*object)[5].material.al = (cl_float2){1.0, 0.4};
	// (*object)[5].object.cylinder.center = (cl_float3){2, 0, 5};
	// (*object)[5].object.cylinder.axis = (cl_float3){0, 1, 0};
	// (*object)[5].object.cylinder.length = 10;
	// (*object)[5].object.cylinder.radius = 1.0f;
}

int			*fill_texture_for_skybox(t_scene *scene)
{
	SDL_Surface *back;
	SDL_Surface *tmp;

	back = IMG_Load("./textures/miami.jpg");
	if (back == NULL)
	{
		ft_putendl(SDL_GetError());
		return (NULL);
	}
	tmp = back;
	back = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
	scene->background = (int *)ft_memalloc(sizeof(int) * back->w * back->h);
	scene->background_h = back->h;
	scene->background_w = back->w;
	ft_memcpy(scene->background, (int *)back->pixels, back->w * back->h * sizeof(int));
	SDL_FreeSurface(back);
	SDL_FreeSurface(tmp);
	// printf("%d %d\n", back->w, back->h);
	return (0);
}

char		**init_files_cl(void)
{
	char		**files;

	files = (char **)ft_memalloc(sizeof(char *) * 4);
	files[0] = "./src_opencl/intersection.cl";
	files[1] = "./src_opencl/uv_mapping.cl";
	files[2] = "./src_opencl/ray_trace.cl";
	files[3] = NULL;
	return (files);
}

int			main(void)
{
	t_rt		*rt;
	char		**files;

	rt = (t_rt *)ft_memalloc(sizeof(t_rt));
	rt->sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	
	sdl_init(rt->sdl);
	
	rt->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	rt->scene->cam.pos = (cl_float3){0.0, 0.0, -10.0};
	rt->scene->cam.phi = 90.0f * M_PI / 180;
	rt->scene->cam.tetta = 90.0f * M_PI / 180;
	init_object(&rt->scene->object);
	init_light(&rt->scene->light);
	rt->opencl = (t_cl *)ft_memalloc(sizeof(t_cl));


	files = init_files_cl();
	read_kernel(rt->opencl, files);

	rt->scene->count_objects = 6;
	rt->scene->count_lights = 1;

	fill_texture_for_skybox(rt->scene);

	calc_screen(&rt->scene->cam);

	create_cl(rt->opencl, rt->sdl, rt->scene);
	sdl_control(rt->sdl, rt->scene, rt->opencl);
	return (0);
}
