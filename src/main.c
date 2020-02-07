/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/02/07 11:04:43 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define NKC_IMPLEMENTATION
#include "rt.h"

#if defined(NKC_EXAMPLE)
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
    sdl_loop(rt);
    return 0;
}
#endif

/*
cc nuklear_cross.c -O2 -Wall -DNKC_EXAMPLE -DNDEBUG -s 
-lm -std=c99 -DNKCD=NKC_SDL  -lSDL2 -framework OpenGL 
-framework Cocoa -framework IOKit -o nkcexample-sdl-gl2.bin 
-I/Users/sleonia/.brew/include/SDL2 -D_THREAD_SAFE  `sdl2-config --libs`
*/
