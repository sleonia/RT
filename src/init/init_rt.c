/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:16:20 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/15 15:11:36 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_value(t_scene *scene,
					t_sdl *sdl)
{
int				i;

	i = -1;
	while (++i < COUNT_OF_TEXTBOX)
	{
		if (i == Phi)
			sprintf(sdl->gui->textbox[i]->text, "%3.3f", scene->cam.phi);
		if (i == Tetta)
			sprintf(sdl->gui->textbox[i]->text, "%3.3f", scene->cam.tetta);
		if (i == Id)
			sprintf(sdl->gui->textbox[i]->text, "%1d", scene->skybox_id);
		if (i == Ambient)
			sprintf(sdl->gui->textbox[i]->text, "%3.3f", scene->ambient);
		if (i == Fsaa)
			sprintf(sdl->gui->textbox[i]->text, "%1d", scene->fsaa);
		if (i == New_obj)
			sprintf(sdl->gui->textbox[i]->text, "%d", 1);
		sdl->gui->textbox[i]->on_focus = false;
	}
}

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
	rt->cl = init_cl(rt);
	set_value(rt->scene, rt->sdl);
	ft_return(&json);
	return (rt);
}
