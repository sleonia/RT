/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2020/01/29 03:15:57 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_light(t_light **light)
{
	*light = (t_light *)ft_memalloc(sizeof(t_light) * 3);
	// (*light)[0].type = 'A';
	// (*light)[0].intensity = 0.2;
	(*light)[0].pos = (cl_float3){0, 1, -100};
	// (*light)[0].type = 'P';
	(*light)[0].intensity = 1.0;
// 	(*light)[2].type = 'D';
// 	(*light)[2].intensity = 0.2;
// 	(*light)[2].pos = (cl_float3){1, 4, 4};
}
