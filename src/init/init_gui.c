/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 04:48:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 11:55:30 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			init_buttons(t_gui *gui)
{
	int				i;

	i = -1;
	while (++i < COUNT_OF_BUTTONS)
	{
		if (!(gui->buttons[i] = (t_button *)ft_memalloc(sizeof(t_button))))
			ft_error(ERROR_INPUT);
	}
}

static void			init_radio_btn(bool *radio_btn)
{
	int				i;

	i = -1;
	while (++i < COUNT_OF_RADIO_BTN)
	{
		radio_btn[i] = false;
	}
}

static t_ttf		*init_ttf(char *font, int font_size, SDL_Color font_color)
{
	t_ttf			*ttf;

	if (TTF_Init() == -1)
		ft_error((char *)SDL_GetError());
	if (!(ttf = (t_ttf *)ft_memalloc((sizeof(t_ttf)))))
		ft_error(ERROR_INPUT);
	ttf->font_size = font_size;
	if (!(ttf->font = TTF_OpenFont(font, ttf->font_size)))
		ft_error((char *)SDL_GetError());
	ttf->font_color = font_color;
	return (ttf);
}

t_gui				*init_gui(void)
{
	t_gui			*gui;

	if (!(gui = (t_gui *)ft_memalloc((sizeof(t_gui)))))
		ft_error(ERROR_INPUT);
	gui->ttf[SMALL_FONT_ID] = init_ttf(FONT, 14, (SDL_Color){255, 255, 255, 0});
	gui->ttf[NORMAL_FONT_ID] = init_ttf(FONT, 24, (SDL_Color){255, 255, 255, 0});
	gui->ttf[BIG_FONT_ID] = init_ttf(FONT, 34, (SDL_Color){255, 255, 255, 0});
	gui->render_text = false;
	if (!(gui->radio = IMG_Load("./assets/gui/radio.png")))
		ft_error((char *)SDL_GetError());
	if (!(gui->radio_click = IMG_Load("./assets/gui/radio_click.png")))
		ft_error((char *)SDL_GetError());
	if (!(gui->scroller = IMG_Load("./assets/gui/scroller.png")))
		ft_error((char *)SDL_GetError());
	if (!(gui->headband = IMG_Load("./assets/textures/pepe2.png")))
		ft_error((char *)SDL_GetError());
	init_buttons(gui);
	init_radio_btn(gui->radio_btn);
	init_textbox(gui);
	return (gui);
}
