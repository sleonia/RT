/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:16:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 15:22:34 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt				*init_rt(char **av)
{
	t_rt			*rt;
	t_key_value		*json;

	if ((rt = (t_rt *)ft_memalloc(sizeof(t_rt))) == NULL)
		ft_error(ERROR_MALLOC);
	if (!(json = parse_json(av[1])))
		ft_error(ERROR_INPUT);
	rt->sdl = init_sdl(json);
	rt->scene = init_scene(json, rt->sdl->sounds);
	rt->opencl = init_cl(json, rt);
	ft_return(&json);
	return (rt);
}
