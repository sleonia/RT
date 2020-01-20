/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/01/20 09:48:15 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_object(t_object **object)
{
	*object = (t_object *)ft_memalloc(sizeof(t_object) * 6);

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

	typedef struct			s_material
{
# ifndef OPENCL___
	cl_float3			color;
# else
	float3				color;
# endif
	float				refraction;
	float				reflection;
	int					texture_id;
}						t_material;

typedef struct			s_object
{
# ifndef OPENCL___
	// union u_objects		*objects;
	cl_float3			center;
	cl_float3			axis;
	float				radius;
# else
	float3				center;
	float3				axis;
	float				radius;
# endif
	enum e_obj_type		type;
	float				tan;
	t_material			material;
}						t_object;
	(*object)[0].type = o_sphere;
	(*object)[0].material.color = (cl_float3){1, 0, 0};
	(*object)[0].material.reflection = 0.9f; // от 0.9 до 1.0
	(*object)[0].material.refraction = 1.8f; // от 1.0 до 1.5
	(*object)[0].material.sp_ex = 50.0f;
	(*object)[0].material.al = (cl_float2){1.0, 1.0};
	(*object)[0].object.sphere.center = (cl_float3){0.0, -2.0, 3};
	(*object)[0].object.sphere.radius = 3.0f;

	(*object)[1].type = o_sphere;
	(*object)[1].material.color = (cl_float3){0, 0, 1};
	(*object)[1].material.reflection = 0.0f;
	(*object)[1].material.refraction = 1.5f;
	(*object)[1].material.sp_ex = 50.0f;
	(*object)[1].material.al = (cl_float2){1.0, 0.4};
	(*object)[1].object.sphere.center = (cl_float3){4, 0, 8};
	(*object)[1].object.sphere.radius = 3.0f;

	(*object)[2].type = o_sphere;
	(*object)[2].material.color = (cl_float3){0, 1, 0};
	(*object)[2].material.reflection = 0.0f;
	(*object)[2].material.refraction = 1.3f;
	(*object)[2].material.sp_ex = 50.0f;
	(*object)[2].material.al = (cl_float2){1.0, 0.4};
	(*object)[2].object.sphere.center = (cl_float3){-4, 0, 8};
	(*object)[2].object.sphere.radius = 3.0f;

	// (*object)[3].type = o_plane;
	// (*object)[3].material.color = (cl_float3){1, 0, 1};
	// (*object)[3].material.reflection = 0.3f;
	// (*object)[3].material.sp_ex = 50.0f;
	// (*object)[3].material.al = (cl_float2){1.0, 0.4};
	// (*object)[3].object.plane.center = (cl_float3){0, 0, 5};
	// (*object)[3].object.plane.axis = (cl_float3){0, 0, 1};
	// (*object)[3].object.plane.dist_z = 10;

	// (*object)[4].type = o_cone;
	// (*object)[4].material.color = (cl_float3){1, 0, 1};
	// (*object)[4].material.reflection = 0.3f;
	// (*object)[4].material.sp_ex = 50.0f;
	// (*object)[4].material.al = (cl_float2){1.0, 0.4};
	// (*object)[4].object.cone.center = (cl_float3){0, 0, 5};
	// (*object)[4].object.cone.axis = (cl_float3){0, 1, 0};
	// (*object)[4].object.cone.length = 10.0f;
	// (*object)[4].object.cone.tan = 0.25;

	// (*object)[5].type = o_cylinder;
	// (*object)[5].material.color = (cl_float3){1, 1, 0};
	// (*object)[5].material.reflection = 0.3f;
	// (*object)[5].material.sp_ex = 50.0f;
	// (*object)[5].material.al = (cl_float2){1.0, 0.4};
	// (*object)[5].object.cylinder.center = (cl_float3){2, 0, 5};
	// (*object)[5].object.cylinder.axis = (cl_float3){0, 1, 0};
	// (*object)[5].object.cylinder.length = 10;
	// (*object)[5].object.cylinder.radius = 1.0f;



	// (*object)[3].type = o_sphere;
	// (*object)[3].color = 0xFFFF00;
	// (*object)[3].reflective = 0.3f;
	// (*object)[3].specular = 300;
	// (*object)[3].center = (cl_float3){0, -5001, 0};
	// (*object)[3].radius = 5000.0f;

	// (*object)[3].type = o_cone;
	// (*object)[3].color = 0xFFFF00;
	// (*object)[3].reflective = 0.3f;
	// (*object)[3].specular = 300;
	// (*object)[3].center = (cl_float3){-3, 0, 10};
	// (*object)[3].axis = (cl_float3){0, 1, 0};
	// (*object)[3].tan = 0.2f;

	// (*object)[4].type = o_cylinder;
	// (*object)[4].color = 0xFF00FF;
	// (*object)[4].reflective = 0.3f;
	// (*object)[4].specular = 300;
	// (*object)[4].center = (cl_float3){3, 0, 7};
	// (*object)[4].axis = (cl_float3){0, 1, 0};
	// (*object)[4].radius = 0.2f;

	// (*object)[5].type = o_plane;
	// (*object)[5].color = 0x00FFFF;
	// (*object)[5].reflective = 0.3f;
	// (*object)[5].specular = 300;
	// (*object)[5].center = (cl_float3){0, -5, 10};
	// (*object)[5].axis = (cl_float3){0, 1, 0};
	// init_sphere_param((*object)[0], (t_sphere_params){(cl_float3){0, -1, 3}, 1.0f, 0xFF0000, 500, 0.2f});
	// init_sphere_param((*object)[1], (t_sphere_params){(cl_float3){2, 0, 4}, 1.0f, 0x0000FF, 500, 0.3f});
	// init_sphere_param((*object)[2], (t_sphere_params){(cl_float3){-2, 0, 4}, 1.0f, 0x00FF00, 10, 0.4f});
	// init_sphere_param((*object)[3], (t_sphere_params){(cl_float3){0, -5001, 0}, 5000.0f, 0xFFFF00, 1000, 0.5f});
	// init_plane_param(object[4], (t_plane_params){{0, 0, 26}, 0x0000FF, 500, 0.4, {0, 0, 1}});
	// init_cylinder_param(object[5], (t_cylinder_params){{0, 2, 5},{1, 0.5, 0}, 0.1, 0xFFFFF0, 500, 0.4});
	// init_cone_param(object[6], (t_cone_params){{0, 3, 5},{0, 1, 0}, 0.2, 0xFF00FF, 500, 0.4});
}

int			*fill_texture_for_skybox(t_sdl *sdl)
{
	int i = 0;
	int j = 0;
	SDL_Surface *back;
	int			*ptr;
	int x = 0;

	back = SDL_LoadBMP("./wood.bmp");
	if (back == NULL)
	{
		printf("%s\n", SDL_GetError());
		return (NULL);
	}
	back = SDL_ConvertSurfaceFormat(back, SDL_PIXELFORMAT_ARGB8888, 0);
	ptr = (int *)back->pixels;
	// printf("%d %d\n", back->w, back->h);
	return (ptr);
}



int			main(void)
{
	t_rtv1		*rtv1;

	rtv1 = (t_rtv1 *)ft_memalloc(sizeof(t_rtv1));
	rtv1->sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	
	sdl_init(rtv1->sdl);
	
	rtv1->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	rtv1->scene->cam.pos = (cl_float3){0.0, 0.0, -10.0};
	rtv1->scene->cam.phi = 90.0f * M_PI / 180;
	rtv1->scene->cam.tetta = 0.001f * M_PI / 180;
	init_object(&rtv1->scene->object);
	init_light(&rtv1->scene->light);
	rtv1->opencl = (t_cl *)ft_memalloc(sizeof(t_cl));
	read_kernel(rtv1->opencl);
	rtv1->scene->count_objects = 6;

	rtv1->sdl->background = fill_texture_for_skybox(rtv1->sdl);

	calc_screen(&rtv1->scene->cam);

	create_cl(rtv1->opencl, rtv1->sdl, rtv1->scene);
	sdl_control(rtv1->sdl, rtv1->scene, rtv1->opencl);
	return (0);
}
