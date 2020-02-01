/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 07:39:52 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_loop(t_sdl *sdl, t_scene *scene, t_cl *cl)
{
	char	quit;

	quit = 0;
	sdl_update(sdl);
	while (!quit)
	{
		events_processing(&quit, sdl, scene, cl);
	}
	sdl_quit(sdl);
}
