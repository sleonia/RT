/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/02/06 22:31:55 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
// #define NKC_IMPLEMENTATION

// enum radioOptions {
//     EASY,
//     HARD
// };

// struct my_nkc_app {
//     struct nkc* nkcHandle;

//     /* some user data */
//     float value;
//     enum radioOptions op;
// };

int			main(int ac, char **av)
{
	t_rt		*rt;

    // struct my_nkc_app myapp;
	if (ac != 2)
		ft_error(ERROR_INPUT);
	rt = init_rt(av);
	change_music(rt->sdl->music);
	calc_screen(&rt->scene->cam);
	set_opencl_arg(rt->opencl, rt->sdl, rt->scene);
	sdl_loop(rt);
	return (0);
}
