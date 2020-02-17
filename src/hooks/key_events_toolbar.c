/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_toolbar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:16:51 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/17 08:03:36 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		search_textbox_in_focus(t_gui *gui)
{
	int			i;

	i = -1;
	while (++i < COUNT_OF_TEXTBOX)
	{
		if (gui->textbox[i]->on_focus)
			return (i);
	}
	return (-1);
}

static void		set_value_from_textbox(t_object *hi_lited_object,
								t_scene *scene,
								t_gui *gui)
{
	if (!hi_lited_object)
	{
		scene->cam.phi = check_phi(ft_atof(gui->textbox[Phi]->text));
		scene->cam.tetta = check_tetta(ft_atof(gui->textbox[Tetta]->text));
		scene->skybox_id = check_skybox(ft_atof(gui->textbox[Id]->text),
										scene->texture_cnt);
		scene->ambient = check_ambient(ft_atof(gui->textbox[Ambient]->text));
		scene->fsaa = check_fsaa(ft_atof(gui->textbox[Fsaa]->text));
	}
}

static void		backspace_processing(int id_cur_textbox, t_gui *gui)
{
	int		len;

	len = ft_strlen(gui->textbox[id_cur_textbox]->text);
	if (len > 1)
	{
		gui->textbox[id_cur_textbox]->text = pop_back(gui->textbox[id_cur_textbox]->text);
		gui->textbox[id_cur_textbox]->render_text = true;
	}
	else if (ft_strlen(gui->textbox[id_cur_textbox]->text) == 1)
	{
		ft_strdel(&gui->textbox[id_cur_textbox]->text);
		gui->textbox[id_cur_textbox]->text = ft_strdup(" ");
		gui->textbox[id_cur_textbox]->render_text = true;
	}
}

static void		text_processing(int id_cur_textbox,
							char *input_text,
							t_gui *gui)
{
	int		len;

	len = ft_strlen(gui->textbox[id_cur_textbox]->text);
	if (len > 7)
		gui->textbox[id_cur_textbox]->on_focus = false;
	gui->textbox[id_cur_textbox]->text =
		ft_strjoin_free(gui->textbox[id_cur_textbox]->text, input_text, 1);
	gui->textbox[id_cur_textbox]->render_text = true;
	len = ft_strlen(gui->textbox[id_cur_textbox]->text);
}

bool			key_toolbar(SDL_Scancode scancode,
						char *flag,
						t_object *hi_lited_object,
						t_rt *rt)
{
	int		id_cur_textbox;

	if (hi_lited_object) //delete
		return (false);
	id_cur_textbox = search_textbox_in_focus(rt->sdl->gui);
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (scancode == SDL_SCANCODE_B)
			SDL_ShowCursor(!SDL_ShowCursor(-1));
		if (scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_TAB)
			change_focus(rt->sdl);
		if (id_cur_textbox != -1)
		{
			if (scancode == SDL_SCANCODE_BACKSPACE)
				backspace_processing(id_cur_textbox, rt->sdl->gui);
			if (scancode == SDL_SCANCODE_RETURN)
				set_value_from_textbox(hi_lited_object, rt->scene, rt->sdl->gui);
		}
	}
	else if(rt->sdl->event.type == SDL_TEXTINPUT)
	{
		if (id_cur_textbox != -1)
			text_processing(id_cur_textbox, rt->sdl->event.text.text, rt->sdl->gui);
	}
	return (false);
}
