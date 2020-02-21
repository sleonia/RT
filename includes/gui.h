/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:40:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 11:25:25 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "rt.h"
# include <SDL.h>
# include <SDL_ttf.h>
# include <stdbool.h>

# define COUNT_OF_BUTTONS	6
# define COUNT_OF_RADIO_BTN	4
# define COUNT_OF_TEXTBOX	35
# define SMALL_FONT_ID		0
# define NORMAL_FONT_ID		1
# define BIG_FONT_ID		2

enum						e_textbox_type
{
	Phi,
	Tetta,
	Id,
	Skybox_ambient,
	Fsaa,
	New_obj,
	Sphere_rad,
	Sphere_center,
	Cylinder_axis,
	Cylinder_center,
	Cylinder_len,
	Cylinder_rad,
	Cone_axis,
	Cone_center,
	Cone_len,
	Cone_tan,
	Plane_axis,
	Plane_tan,
	Parab_axis,
	Parab_center,
	Parab_dist,
	Parab_len,
	Torus_axis,
	Torus_center,
	Torus_bigr,
	Torus_r,
	Mtrl_Color,
	Mtrl_ambient,
	Mtrl_diffuse,
	Mtrl_specular,
	Mtrl_reflection,
	Mtrl_refraction,
	Mtrl_texture_id,
};

typedef struct				s_textbox
{
	SDL_Texture				*m_texture;
	char					*text;
	int						type;
	int						m_width;
	int						m_height;
	SDL_Color				color;
	bool					render_text;
	bool					on_focus;
	SDL_Rect				pos;
	bool					is_changed;
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
	t_ttf					*ttf[3];
	t_textbox				*textbox[COUNT_OF_TEXTBOX];
	SDL_Surface				*headband;
}							t_gui;

#endif
