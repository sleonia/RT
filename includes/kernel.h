/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:23:27 by deladia           #+#    #+#             */
/*   Updated: 2020/01/20 12:20:10 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H
# include "rtv1.h"
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

#endif
