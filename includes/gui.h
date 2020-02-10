/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:40:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 15:46:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "rt.h"
# include <SDL.h>
# include <SDL_ttf.h>
# include <stdbool.h>

# define COUNT_OF_BUTTONS	10
# define COUNT_OF_RADIO_BTN	4
# define COUNT_OF_TEXTBOX	10

enum						e_textbox_type
{
	phi,
	position,
	tetta,
	id,
	ambient,
	fsaa,
	new_obj
};

typedef struct				s_textbox
{
	SDL_Texture				*m_texture;
	char					*text;
	int						type;
	int						m_width;
	int						m_height;
}							t_textbox;


typedef struct				s_button
{
	char					*text;
	SDL_Color				clr_button;
	SDL_Color				clr_border;
	SDL_Rect				rect_borders;
	SDL_Rect				rect_body;
}							t_button;

typedef struct				s_ttf
{
	TTF_Font				*font;
	int						font_size;
	SDL_Color				font_color;
}							t_ttf;

typedef struct				s_gui
{
	bool					render_text;
	char					*input_text;
	char					*new_input_text;
	bool					radio_btn[COUNT_OF_RADIO_BTN];
	SDL_Surface				*radio;
	SDL_Surface				*radio_click;
	SDL_Surface				*scroller;
	t_button				*buttons[COUNT_OF_BUTTONS];
	t_ttf					*ttf[2];
	t_textbox				*textbox[COUNT_OF_TEXTBOX];
}							t_gui;

#endif
