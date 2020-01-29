/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:23:27 by deladia           #+#    #+#             */
/*   Updated: 2020/01/29 01:17:22 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H
# include "rt.h"
# define WIDTH 1280
# define HEIGHT 1024
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define MAX_DIST 10000.f
# define RED(color) (((int)color >> 16) & 0xFF)
# define GREEN(color) (((int)color >> 8) & 0xFF)
# define BLUE(color) ((int)color & 0xFF)


typedef struct			t_hitting
{
# ifndef OPENCL___
	cl_float3			n;
	cl_float3			hit;
# else
	float3				n;
	float3				hit;
# endif
	t_material			mat;
}						t_hitting;

int						closest_intersection(float3 o, float3 d, int count_obj, __global t_object *obj, t_hitting *light_hit, __global int *texture, __global int *texture_param);
float3					uv_mapping_for_skybox(__global int *skybox, float3 d, __global int *tex_param, const int text_id);
int						ft_sign(float a);
float3					ft_normalize(float3 vec);
float2					uv_mapping_for_sphere(t_hitting *light_hit);
float2					uv_mapping_for_plane(t_hitting *light_hit);
float2 			uv_mapping_for_cone(t_hitting *light_hit, __global t_cone *cone);
float2			uv_mapping_for_cylinder(t_hitting *light_hit, __global t_cylinder *cylinder);
void					normalize_coord_for_texture(float2 uv, float3 *color, __global int *texture,  __global int *texture_param, int texture_id);
#endif
