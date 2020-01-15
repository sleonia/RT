/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2020/01/15 22:45:42 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_light(t_light **light)
{
	*light = (t_light *)ft_memalloc(sizeof(t_light) * 3);
	// (*light)[0].type = 'A';
	// (*light)[0].intensity = 0.2;
	(*light)[0].pos = (cl_float3){3, 1, -10};
	// (*light)[0].type = 'P';
	(*light)[0].intensity = 0.6;
// 	(*light)[2].type = 'D';
// 	(*light)[2].intensity = 0.2;
// 	(*light)[2].pos = (cl_float3){1, 4, 4};
}
