/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:05:14 by deladia           #+#    #+#             */
/*   Updated: 2019/12/11 16:34:16 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_light(t_light **light)
{
	*light = (t_light *)ft_memalloc(sizeof(t_light) * 3);
	(*light)[0].type = 'A';
	(*light)[0].intensity = 0.2;
	(*light)[1].pos = (cl_float3){3, 1, -1};
	(*light)[1].type = 'P';
	(*light)[1].intensity = 0.6;
	(*light)[2].type = 'D';
	(*light)[2].intensity = 0.2;
	(*light)[2].pos = (cl_float3){1, 4, 4};
}
