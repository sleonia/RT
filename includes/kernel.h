/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:23:27 by deladia           #+#    #+#             */
/*   Updated: 2020/01/15 23:06:46 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H
# include "rtv1.h"
# define WIDTH 1280
# define HEIGHT 1024
// # define VW 1.25
// # define VH 1
// # define D 1
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define MAX_DIST 10000.f
# define RED(color) (((int)color >> 16) & 0xFF)
# define GREEN(color) (((int)color >> 8) & 0xFF)
# define BLUE(color) ((int)color & 0xFF)


typedef struct			t_lighting
{
# ifndef OPENCL___
	cl_float3			n;
	cl_float3			hit;
# else
	float3				n;
	float3				hit;
# endif
	t_material			mat;
}						t_lighting;



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


#endif
