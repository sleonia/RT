/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:59:09 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/30 17:03:04 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_objects(t_object **object, int nbr)
{
	if (!(*object = (t_object *)ft_memalloc(sizeof(t_object) * (nbr + 1))))
		ft_error("MALLOC_ERROR");
}