/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/01/29 04:52:05 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_object(t_object **object)
{
	*object = (t_object *)ft_memalloc(sizeof(t_object) * 11);

	(*object)[0].type = o_sphere;
	(*object)[0].material.color = (cl_float3){1, 1, 1};
	(*object)[0].material.reflection = 0.0f; // от 0.1 до 1.0
	(*object)[0].material.refraction = 0.0f; // от 1.0 до 1.3
	(*object)[0].material.specular = 100.0f;
	(*object)[0].material.ambient = 1.0;
	(*object)[0].material.diffuse = 0.4;
	(*object)[0].object.sphere.center = (cl_float3){0.0, -2.0, 3.0};
	(*object)[0].object.sphere.radius = 2.0f;
	(*object)[0].material.texture_id = 1;

	// (*object)[10].type = o_sphere;
	// (*object)[10].material.color = (cl_float3){1, 1, 1};
	// (*object)[10].material.reflection = 0.9f; // от 0.1 до 1.0
	// (*object)[10].material.refraction = 0.0f; // от 1.0 до 1.3
	// (*object)[10].material.specular = 100.0f;
	// (*object)[10].material.ambient = 1.0;
	// (*object)[10].material.diffuse = 0.4;
	// (*object)[10].object.sphere.center = (cl_float3){0.0, 6.0, 8.0};
	// (*object)[10].object.sphere.radius = 2.0f;
	// (*object)[10].material.texture_id = -1;

	// (*object)[8].type = o_sphere;
	// (*object)[8].material.color = (cl_float3){1, 1, 1};
	// (*object)[8].material.reflection = 0.0f; // от 0.1 до 1.0
	// (*object)[8].material.refraction = 0.0f; // от 1.0 до 1.3
	// (*object)[8].material.specular = 100.0f;
	// (*object)[8].material.ambient = 1.0;
	// (*object)[8].material.diffuse = 0.4;
	// (*object)[8].object.sphere.center = (cl_float3){-5.0, 0.0, 0.0};
	// (*object)[8].object.sphere.radius = 3.0f;
	// (*object)[8].material.texture_id = 5;

	// (*object)[9].type = o_sphere;
	// (*object)[9].material.color = (cl_float3){1, 1, 1};
	// (*object)[9].material.reflection = 0.0f; // от 0.1 до 1.0
	// (*object)[9].material.refraction = 0.0f; // от 1.0 до 1.3
	// (*object)[9].material.specular = 100.0f;
	// (*object)[9].material.ambient = 1.0;
	// (*object)[9].material.diffuse = 0.4;
	// (*object)[9].object.sphere.center = (cl_float3){6.0, -5.0, 3.0};
	// (*object)[9].object.sphere.radius = 3.0f;
	// (*object)[9].material.texture_id = 6;

	(*object)[1].type = o_sphere;
	(*object)[1].material.color = (cl_float3){1, 1, 1};
	(*object)[1].material.reflection = 0.1f;
	(*object)[1].material.refraction = 0.0f;
	(*object)[1].material.specular = 100.0f;
	(*object)[1].material.ambient = 1.0;
	(*object)[1].material.diffuse = 0.4;
	(*object)[1].object.sphere.center = (cl_float3){4, 0, 8};
	(*object)[1].object.sphere.radius = 2.0f;
	(*object)[1].material.texture_id = -1;

	(*object)[2].type = o_sphere;
	(*object)[2].material.color = (cl_float3){1, 1, 1};
	(*object)[2].material.reflection = 0.1f;
	(*object)[2].material.refraction = 0.0f;
	(*object)[2].material.specular = 100.0f;
	(*object)[2].material.ambient = 1.0;
	(*object)[2].material.diffuse = 0.4;
	(*object)[2].object.sphere.center = (cl_float3){-4, 0, 8};
	(*object)[2].object.sphere.radius = 2.0f;
	(*object)[2].material.texture_id = -1;

	// (*object)[3].type = o_plane;
	// (*object)[3].material.color = (cl_float3){1, 1, 1};
	// (*object)[3].material.reflection = 0.f;
	// (*object)[3].material.refraction = 0.f;
	// (*object)[3].material.specular = 100.0f;
	// (*object)[3].material.ambient = 1.0;
	// (*object)[3].material.diffuse = 0.4;
	// (*object)[3].object.plane.axis = (cl_float3){0, 0, 1};
	// (*object)[3].object.plane.dist = 10;
	// (*object)[3].material.texture_id = 2;

	// (*object)[4].type = o_plane;
	// (*object)[4].material.color = (cl_float3){0, 1, 1};
	// (*object)[4].material.reflection = 0.9f;
	// (*object)[4].material.refraction = 0.f;
	// (*object)[4].material.specular = 100.0f;
	// (*object)[4].material.ambient = 1.0;
	// (*object)[4].material.diffuse = 0.4;
	// (*object)[4].object.plane.axis = (cl_float3){1, 0, 0};
	// (*object)[4].object.plane.dist = 10;
	// (*object)[4].material.texture_id = -1;

	// (*object)[5].type = o_plane;
	// (*object)[5].material.color = (cl_float3){0, 1, 1};
	// (*object)[5].material.reflection = 0.9f;
	// (*object)[5].material.refraction = 0.f;
	// (*object)[5].material.specular = 100.0f;
	// (*object)[5].material.ambient = 1.0;
	// (*object)[5].material.diffuse = 0.4;
	// (*object)[5].object.plane.axis = (cl_float3){-1, 0, 0};
	// (*object)[5].object.plane.dist = 10;
	// (*object)[5].material.texture_id = -1;

	// (*object)[6].type = o_plane;
	// (*object)[6].material.color = (cl_float3){1, 1, 1};
	// (*object)[6].material.reflection = 0.f;
	// (*object)[6].material.refraction = 0.f;
	// (*object)[6].material.specular = 100.0f;
	// (*object)[6].material.ambient = 1.0;
	// (*object)[6].material.diffuse = 0.4;
	// (*object)[6].object.plane.axis = (cl_float3){0, 1, 0};
	// (*object)[6].object.plane.dist = 10;
	// (*object)[6].material.texture_id = 0;

	// (*object)[7].type = o_plane;
	// (*object)[7].material.color = (cl_float3){1, 1, 1};
	// (*object)[7].material.reflection = 0.f;
	// (*object)[7].material.refraction = 0.f;
	// (*object)[7].material.specular = 100.0f;
	// (*object)[7].material.ambient = 1.0;
	// (*object)[7].material.diffuse = 0.4;
	// (*object)[7].object.plane.axis = (cl_float3){0, -1, 0};
	// (*object)[7].object.plane.dist = 10;
	// (*object)[7].material.texture_id = 0;

	// (*object)[8].type = o_plane;
	// (*object)[8].material.color = (cl_float3){1, 1, 1};
	// (*object)[8].material.reflection = 0.f;
	// (*object)[8].material.refraction = 0.f;
	// (*object)[8].material.specular = 100.0f;
	// (*object)[8].material.ambient = 1.0;
	// (*object)[8].material.diffuse = 0.4;
	// (*object)[8].object.plane.axis = (cl_float3){0, 0, -1};
	// (*object)[8].object.plane.dist = 15;
	// (*object)[8].material.texture_id = 0;

	(*object)[4].type = o_cone;
	(*object)[4].material.color = (cl_float3){1, 0, 1};
	(*object)[4].material.reflection = 0.0f;
	(*object)[4].material.refraction = 0.f;
	(*object)[4].material.specular = 50.0f;
	(*object)[4].material.ambient = 1.0;
	(*object)[4].material.diffuse = 0.4;
	(*object)[4].object.cone.center = (cl_float3){0, 0, 5};
	(*object)[4].object.cone.axis = (cl_float3){1, 1, 0};
	cl_to_norm(&(*object)[4].object.cone.axis);
	(*object)[4].object.cone.length = 10.0f;
	(*object)[4].object.cone.tan = 0.25;
	(*object)[4].material.texture_id = 0;

	(*object)[3].type = o_cylinder;
	(*object)[3].material.color = (cl_float3){1, 1, 0};
	(*object)[3].material.refraction = 0.0f;
	(*object)[3].material.reflection = 0.f;
	(*object)[3].material.specular = 50.0f;
	(*object)[3].material.ambient = 1.0;
	(*object)[3].material.diffuse = 0.4;
	(*object)[3].object.cylinder.center = (cl_float3){0, 8, 8};
	(*object)[3].object.cylinder.axis = (cl_float3){1, 1, 0};
	cl_to_norm(&(*object)[3].object.cylinder.axis);
	(*object)[3].object.cylinder.length = 10;
	(*object)[3].object.cylinder.radius = 1.0f;
	(*object)[3].material.texture_id = 0;

	// (*object)[9].type = o_cylinder;
	// (*object)[9].material.color = (cl_float3){1, 1, 0};
	// (*object)[9].material.refraction = 0.0f;
	// (*object)[9].material.reflection = 0.1f;
	// (*object)[9].material.specular = 50.0f;
	// (*object)[9].material.ambient = 1.0;
	// (*object)[9].material.diffuse = 0.4;
	// (*object)[9].object.cylinder.center = (cl_float3){9, 0, 9};
	// (*object)[9].object.cylinder.axis = (cl_float3){0, 1, 0};
	// (*object)[9].object.cylinder.length = 10;
	// (*object)[9].object.cylinder.radius = 1.0f;
	// (*object)[9].material.texture_id = -1;

	// (*object)[10].type = o_cone;
	// (*object)[10].material.color = (cl_float3){1, 1, 0};
	// (*object)[10].material.refraction = 0.0f;
	// (*object)[10].material.reflection = 0.9f;
	// (*object)[10].material.specular = 50.0f;
	// (*object)[10].material.ambient = 1.0;
	// (*object)[10].material.diffuse = 0.4;
	// (*object)[10].object.cone.center = (cl_float3){0, 2, 7};
	// (*object)[10].object.cone.axis = (cl_float3){0, 1, 0};
	// (*object)[10].object.cone.length = 10;
	// (*object)[10].object.cone.tan = 0.25f;
	// (*object)[10].material.texture_id = -1;
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
	change_music(rt);
	rt->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	rt->scene->cam.pos = (cl_float3){0.0, 0.0, -14.0};
	rt->scene->cam.phi = 90.0f * M_PI / 180;
	rt->scene->cam.tetta = 90.0f * M_PI / 180;
	init_light(&rt->scene->light);
	rt->opencl = (t_cl *)ft_memalloc(sizeof(t_cl));


	files = init_files_cl();
	read_kernel(rt->opencl, files);

	rt->scene->count_objects = 11;
	rt->scene->count_lights = 1;
	rt->scene->skybox_id = 0;
	init_object(&rt->scene->object);

	realloc_img(rt->scene, "./textures/sample.jpg");
	realloc_img(rt->scene, "./textures/marble.jpg");


	calc_screen(&rt->scene->cam);

	create_cl(rt->opencl, rt->sdl, rt->scene);
	sdl_control(rt->sdl, rt->scene, rt->opencl);
	return (0);
}
