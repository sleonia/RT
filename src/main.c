/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/02/21 05:30:14 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(int ac, char **av)
{
	t_rt		*rt;

	if (ac != 2)
		ft_error(ERROR_INPUT);
	rt = init_rt(av);
	change_music(rt->sdl->music);
	calc_screen(&rt->scene->cam);
	create_kernel_rt(rt->cl);
	set_opencl_arg(rt->cl, rt->sdl, rt->scene);
	sdl_loop(rt);
	return (0);
}
