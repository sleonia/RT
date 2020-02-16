/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_toolbar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:16:51 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/16 21:49:01 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				search_textbox_in_focus(t_gui *gui)
{
	int			i;

	i = -1;
	while (++i < COUNT_OF_TEXTBOX)
	{
		if (gui->textbox[i]->on_focus)
			return (i);
	}
	return (-1);
	// gui->textbox[4]->on_focus = true;
	// return (4);
}

void			set_value_textbox(t_object *hi_lited_object, t_rt *rt)
{
	// printf("%d\n", rt->scene->texture_cnt);
	if (!hi_lited_object)
	{
		rt->scene->cam.phi = check_phi(ft_atof(rt->sdl->gui->textbox[Phi]->text));
		rt->scene->cam.tetta = check_tetta(ft_atof(rt->sdl->gui->textbox[Tetta]->text));
		rt->scene->skybox_id = check_skybox(ft_atof(rt->sdl->gui->textbox[Id]->text), rt->scene->texture_cnt);
		rt->scene->ambient = check_ambient(ft_atof(rt->sdl->gui->textbox[Ambient]->text));
		rt->scene->fsaa = check_fsaa(ft_atof(rt->sdl->gui->textbox[Fsaa]->text));
	}
}

bool			key_toolbar(SDL_Scancode scancode,
						char *flag,
						t_object *hi_lited_object,
						t_rt *rt)
{
	int		len;
	int		id_cur_textbox;

	if (hi_lited_object)
		return (false);
	id_cur_textbox = search_textbox_in_focus(rt->sdl->gui);
	// printf("id_cur_textbox = %d\n", id_cur_textbox);
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (scancode == SDL_SCANCODE_B)
			SDL_ShowCursor(!SDL_ShowCursor(-1));
		if (scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_TAB)
			change_focus(rt->sdl);
		// if ((id_cur_textbox = search_textbox_in_focus(rt->sdl->gui)) == -1)
			// return (false);
		if (id_cur_textbox != -1)
		{
			len = ft_strlen(rt->sdl->gui->textbox[id_cur_textbox]->text);
			if (scancode == SDL_SCANCODE_BACKSPACE && len > 1)
			{
				rt->sdl->gui->textbox[id_cur_textbox]->text = pop_back(rt->sdl->gui->textbox[id_cur_textbox]->text);
				rt->sdl->gui->textbox[id_cur_textbox]->render_text = true;
			}
			else if (scancode == SDL_SCANCODE_BACKSPACE && ft_strlen(rt->sdl->gui->textbox[id_cur_textbox]->text) == 1)
			{
				ft_strdel(&rt->sdl->gui->textbox[id_cur_textbox]->text);
				rt->sdl->gui->textbox[id_cur_textbox]->text = ft_strdup(" ");
				rt->sdl->gui->textbox[id_cur_textbox]->render_text = true;
			}
			if (scancode == SDL_SCANCODE_RETURN)
				set_value_textbox(hi_lited_object, rt);
				// rt->scene->cam.phi = ft_atof(rt->sdl->gui->textbox[id_cur_textbox]->text);
			// rt->sdl->gui->textbox[id_cur_textbox]->on_focus = false;
		}
	}
	else if(rt->sdl->event.type == SDL_TEXTINPUT)
	{
		if (id_cur_textbox != -1)
		{
			// printf("%s\n", rt->sdl->event.text.text);
			len = ft_strlen(rt->sdl->gui->textbox[id_cur_textbox]->text);
			if (len > 7)
			{
				rt->sdl->gui->textbox[id_cur_textbox]->on_focus = false;
				return (false);
			}
			rt->sdl->gui->textbox[id_cur_textbox]->text = ft_strjoin_free(rt->sdl->gui->textbox[id_cur_textbox]->text, rt->sdl->event.text.text, 1);
			// printf("%s\n", rt->sdl->gui->textbox[id_cur_textbox]->text);
			rt->sdl->gui->textbox[id_cur_textbox]->render_text = true;
			// rt->sdl->gui->textbox[id_cur_textbox]->on_focus = false;
			// rt->sdl->gui->textbox[!id_cur_textbox]->on_focus = true;
		}
	}
	return (false);
}
