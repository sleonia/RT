/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:09:13 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 12:23:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		textbox_update(t_object *select_obj,
							t_gui *gui,
							SDL_Renderer *render)
{
	if (!select_obj)
		render_textboxs(Phi, Fsaa, gui, render);
	else if (select_obj->type == o_sphere)
		render_textboxs(Sphere_rad, Sphere_center, gui, render);
	else if (select_obj->type == o_cylinder)
		render_textboxs(Cylinder_axis, Cylinder_rad, gui, render);
	else if (select_obj->type == o_cone)
		render_textboxs(Cone_axis, Cone_tan, gui, render);
	else if (select_obj->type == o_plane)
		render_textboxs(Plane_axis, Plane_tan, gui, render);
	else if (select_obj->type == o_parab)
		render_textboxs(Parab_axis, Parab_len, gui, render);
	else if (select_obj->type == o_torus)
		render_textboxs(Torus_axis, Torus_r, gui, render);
	if (select_obj)
		render_textboxs(Mtrl_Color, Mtrl_texture_id, gui, render);
}

void			sdl_update(t_object *select_obj, t_sdl *sdl)
{
	int			i;

	i = -1;
	while (++i < CNT_OF_DISPLAYS)
	{
		SDL_UpdateTexture(sdl->screen[i]->texture,
						NULL, sdl->screen[i]->sur->pixels,
						(i == 0 ? WIDTH : TOOL_SCREEN_WIDTH) * sizeof(int));
		SDL_RenderCopy(sdl->screen[i]->render, sdl->screen[i]->texture,
					NULL, NULL);
		if (i == 1 && sdl->screen[1]->keyboard_focus)
			textbox_update(select_obj, sdl->gui, sdl->screen[i]->render);
		SDL_RenderPresent(sdl->screen[i]->render);
	}
}
