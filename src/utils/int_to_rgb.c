/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:35:41 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 11:36:09 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_int3				int_to_rgb(int src_color)
{
	cl_int3			color;

	color.x = (src_color >> 16) & 0xFF;
	color.y = (src_color >> 8) & 0xFF;
	color.z = (src_color) & 0xFF;
	return (color);
}
