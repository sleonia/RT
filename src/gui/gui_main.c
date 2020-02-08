/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:54:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 06:58:29 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gui_main(t_object **hi_lited_object, t_sdl *sdl)
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t k = 0; k < 500; k++)
			((int *)(sdl->screen[1]->sur->pixels))[i * 500 + k] = 0x2C3852;
	}
	if (!*hi_lited_object)
		gui_default_screen(hi_lited_object, sdl);
	else if ((*hi_lited_object)->type == o_sphere)
		sdl_putstr(100, 100, "PIDOR0", sdl);
	else if ((*hi_lited_object)->type == o_cylinder)
		sdl_putstr(100, 100, "PIDOR1", sdl);
	else if ((*hi_lited_object)->type == o_cone)
		sdl_putstr(100, 100, "PIDOR2", sdl);
	else if ((*hi_lited_object)->type == o_plane)
		sdl_putstr(100, 100, "PIDOR3", sdl);
	else if ((*hi_lited_object)->type == o_parab)
		sdl_putstr(100, 100, "PIDOR4", sdl);
}
