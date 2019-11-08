/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:26:17 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 14:26:19 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_pos		*matrix_on_vector(double a, double b, t_pos *vec)
{
	double	x;
	double	y;
	double	z;
	double	b_to_rad;
	double	a_to_rad;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	b_to_rad = (b * M_PI) / 180;
	a_to_rad = (a * M_PI) / 180;
	vec->x = x * cos(b_to_rad) + z * sin(b_to_rad);
	vec->y = (x * sin(b_to_rad) - z * cos(b_to_rad)) * sin(a_to_rad) + y
		* cos(a_to_rad);
	vec->z = ((z * cos(b_to_rad) - x * sin(b_to_rad)) * cos(a_to_rad)) + y
		* sin(a_to_rad);
	return (vec);
}

/*
** Скалярное произведение векторов
*/

t_pos		vector_normalize(t_pos *a)
{
	float	len;
	t_pos	vec;

	vec = *a;
	len = vector_len(a);
	if (len == 0)
		return (vec);
	vec = vector_on_number(a, 1 / len);
	return (vec);
}

double		dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_pos		v_plus(t_pos v1, t_pos v2)
{
	t_pos	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

t_pos		v_minus(t_pos v1, t_pos v2)
{
	t_pos	new_v;

	new_v.x = v1.x - v2.x;
	new_v.y = v1.y - v2.y;
	new_v.z = v1.z - v2.z;
	return (new_v);
}
