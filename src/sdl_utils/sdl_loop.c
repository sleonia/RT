/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 13:27:30 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_loop(t_sdl *sdl, t_scene *scene, t_cl *cl)
{
	char	flag;

	flag = 0;
	sdl_update(sdl);
	while (flag != 1)
	{
		events_processing(&flag, sdl, scene, cl);
	}
	sdl_quit(sdl);
}
