/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:16:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 10:22:54 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt		*init_rt(void)
{
	t_rt	*rt;

	rt = (t_rt *)ft_memalloc(sizeof(t_rt));
	rt->sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	return (rt);
}
