/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:16:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 19:24:51 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt		*init_rt(char **av)
{
	t_rt	*rt;

	rt = (t_rt *)ft_memalloc(sizeof(t_rt));
	if (!(rt->json = parse_json(av[1])))
		ft_error("ERROR_INPUTz");
	rt->sdl = init_sdl(rt->json);
	// rt->opencl = ;
	return (rt);
}
