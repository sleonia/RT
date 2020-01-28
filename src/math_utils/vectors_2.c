/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:06:06 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 13:28:38 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// t_pos		*matrix_on_vector(double a, double b, t_pos *vec)
// {
// 	double	x;
// 	double	y;
// 	double	z;

// 	x = vec->x;
// 	y = vec->y;
// 	z = vec->z;
// 	vec->x = x * cos(b) + z * sin(b);
// 	vec->y = (x * sin(b) - z * cos(b)) * sin(a) + y * cos(a);
// 	vec->z = (z * cos(b) - x * sin(b)) + y * sin(a);
// 	return (vec);
// }

/*
** Скалярное произведение векторов
*/

// double		ft_dot(t_pos *a, t_pos *b)
// {
// 	return (a->x * b->x + a->y * b->y + a->z * b->z);
// }

// t_pos		v_plus(t_pos v1, t_pos v2)
// {
// 	t_pos	new_v;

// 	new_v.x = v1.x + v2.x;
// 	new_v.y = v1.y + v2.y;
// 	new_v.z = v1.z + v2.z;
// 	return (new_v);
// }

// t_pos		v_minus(t_pos v1, t_pos v2)
// {
// 	t_pos	new_v;

// 	new_v.x = v1.x - v2.x;
// 	new_v.y = v1.y - v2.y;
// 	new_v.z = v1.z - v2.z;
// 	return (new_v);
// }