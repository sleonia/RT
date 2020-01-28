/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/01/28 19:09:52 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


int			main(int ac, char **av)
{
	t_rt		*rt;

	if (ac != 2)
		ft_error(ERROR_INPUT);
	rt = init_rt(av);
	change_music(rt);
	sdl_loop(rt->sdl, rt->scene, rt->opencl);
	return (0);
}
