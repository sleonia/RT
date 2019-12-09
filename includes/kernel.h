/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:23:27 by deladia           #+#    #+#             */
/*   Updated: 2019/12/09 20:09:04 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H
# ifndef OPENCL___
# include <math.h>
# include <OpenCL/opencl.h>
# endif
# define WIDTH 1250
# define HEIGHT 1000
# define VW 1.25
# define VH 1
# define D 1
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef struct			s_result
{
	float 				t1;
	float 				t2;
}						t_result;

typedef struct			s_cam
{
# ifndef OPENCL___
	cl_float3			pos;
# else
	float3				pos;
# endif
	float				a;
	float				b;
}						t_cam;

typedef struct 			s_light
{
# ifndef OPENCL___
	cl_float3			pos;
# else
	float3				pos;
# endif
	char 				type;
	float 				intensity;
}						t_light;

typedef struct 			s_light_off
{
	int					ambient;
	int					point;
	int					directional;
	int					reflect;
}						t_light_off;

// typedef struct 			s_cylinder
// {
// # ifndef OPENCL___	
// 	cl_float3			center;
// 	cl_float3			axis;
// # else
// 	float3				center;
// 	float3				axis;
// # endif
// 	float				radius;
// }						t_cylinder;

// typedef struct 			s_cone
// {
// # ifndef OPENCL___	
// 	cl_float3			center;
// 	cl_float3			axis;
// # else
// 	float3				center;
// 	float3				axis;
// # endif
// 	float				tan;
// }						t_cone;

// typedef struct 			s_plane
// {
// # ifndef OPENCL___
// 	cl_float3			center;
// 	cl_float3			normal;
// # else
// 	float3				normal;
// 	float3				center;
// # endif
// }						t_plane;

// typedef struct 			s_sphere
// {
// # ifndef OPENCL___
// 	cl_float3			center;
// 	float				radius;
// # else
// 	float3				center;
// 	float				radius;
// # endif

// }						t_sphere;

// union					u_objects
// {
// 	t_sphere			sphere;
// 	t_cylinder			cylinder;
// 	t_cone				cone;
// 	t_plane				plane;
// };

enum					e_obj_type
{
	o_sphere = 1,
	o_cylinder,
	o_cone,
	o_plane,
};

typedef struct			s_object
{
# ifndef OPENCL___
	// union u_objects		*objects;
	cl_float3			center;
	float				radius;
	cl_float3			normal;
	cl_float3			axis;
# else
	float3				center;
	float				radius;
	float3				normal;
	float3				axis;
# endif
	enum e_obj_type		type;
	int					color;
	int					specular;
	float				reflective;
	float				tan;
}						t_object;

typedef struct			s_return
{
	int					closest_object;
	float				closest_t;
}						t_return;

typedef struct			s_scene
{
# ifndef OPENCL___
	cl_float3			view;
# else
	float3				view;
# endif
	t_light				*light;
	t_cam				*cam;
	t_object			*object;
	t_light_off			*off;
}						t_scene;

#endif
