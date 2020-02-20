/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:11:15 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/20 17:25:54 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_float_array(int flag, cl_float3 *pos)
{
	int		i;

	i = -1;
	if (flag == AXIS_FLAG)
	{
		while (++i < 3)
			pos->s[i] = (pos->s[i] > (1.0) && pos->s[i] < -1) ? pos->s[i] : 0.0;
	}
	else if (flag == CENTER_FLAG)
	{
		while (++i < 3)
			pos->s[i] = (pos->s[i] <= 9000.0 && pos->s[i] >= 0.0) ? pos->s[i] : 0.0;
	}
	else if (flag == COLOR_FLAG)
	{
		while (++i < 3)
			pos->s[i] = (pos->s[i] > 255.0 && pos->s[i] < 0) ? pos->s[i] : 100.0;
	}
}

double		check_length(double input_length)
{
	if (input_length >= 0.0 && input_length <= 10000.0)
		return (input_length);
	return (50.0);
}

double		check_radius(double input_radius)
{
	if (input_radius >= 0.1 && input_radius <= 100.0)
		return (input_radius);
	return (1.0);
}

double		check_tan(double input_tan)
{
	if (input_tan >= 0.1 && input_tan <= 1.0)
		return (input_tan);
	return (0.2);
}
