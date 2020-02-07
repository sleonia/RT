/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/02/07 21:07:58 by sleonia          ###   ########.fr       */
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
    create_kernel_rt(rt->opencl, rt->scene);
    set_opencl_arg(rt->opencl, rt->sdl, rt->scene);	
    // SDL_SetWindowSize(rt->sdl->window, WIDTH + 500, HEIGHT);
    sdl_loop(rt);
    return 0;
}
