/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:59:09 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/04 13:18:22 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_objects(t_object **object, int nbr)
{
	if (!(*object = (t_object *)ft_memalloc(sizeof(t_object) * (nbr))))
		ft_error("MALLOC_ERROR");
}
