/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:20:37 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/07 01:27:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			init_sdl_music(t_key_value *assets, t_sdl *sdl)
{
	int				i;

	i = 0;
	while (++i < NBR_OF_SONGS)
		sdl->music[i] = NULL;
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	initAudio();
	parse_music_json(assets, sdl);
	sdl->volume = parse_volume_json(assets);
	Mix_VolumeMusic(sdl->volume);
	parse_sounds_json(assets, sdl);
}

static void			set_window_icon(t_key_value *assets, t_sdl *sdl)
{
	char			*icon;
	SDL_Surface		*sur_win;
	SDL_Surface		*sur_img;
	SDL_Surface		*conv_sur_img;

	if (!(icon = parse_icon_json(assets, sdl)))
		return ;
	if (!(sur_win = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0xFF000000,
										0x00FF0000, 0x0000FF00, 0x000000FF)))
		ft_error((char *)SDL_GetError());
	if (!(sur_img = IMG_Load(icon)))
		ft_error((char *)SDL_GetError());
	if (!(conv_sur_img = SDL_ConvertSurface(sur_img, sur_win->format, 0)))
		ft_error((char *)SDL_GetError());
	SDL_FreeSurface(sur_win);
	SDL_FreeSurface(sur_img);
	SDL_SetWindowIcon(sdl->window, conv_sur_img);
	SDL_FreeSurface(conv_sur_img);
	ft_strdel(&icon);
}

static void			init_ttf(t_sdl *sdl)
{
	if (TTF_Init() == -1)
		ft_error((char *)SDL_GetError());
	sdl->font_size = 25;
	if (!(sdl->font = TTF_OpenFont(FONT, sdl->font_size)))
		ft_error((char *)SDL_GetError());
	sdl->font_color = (SDL_Color){255, 255, 255, 0};
}

static void			init_sdl_2(t_key_value *json, t_sdl *sdl)
{
	t_key_value		*assets;

	SDL_UpdateTexture(sdl->texture, NULL, sdl->sur->pixels,
					WIDTH * sizeof(int));
	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	assets = parse_assets(json, sdl);
	set_window_icon(assets, sdl);
	init_sdl_music(assets, sdl);
	init_ttf(sdl);
}

t_sdl				*init_sdl(t_key_value *json)
{
	t_sdl			*sdl;

	if ((sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)))) == NULL)
		ft_error(ERROR_INPUT);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		ft_error((char *)SDL_GetError());
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
		ft_error((char *)SDL_GetError());
	if (!(sdl->window = SDL_CreateWindow("RT", 350,
			200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error((char *)SDL_GetError());
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_error((char *)SDL_GetError());
	if (!(sdl->texture = SDL_CreateTexture(sdl->render,
										SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIDTH, HEIGHT)))
		ft_error((char *)SDL_GetError());
	if (!(sdl->sur = SDL_CreateRGBSurface(0, WIDTH,
			HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF)))
		ft_error((char *)SDL_GetError());
	sdl->help_screen_flag = true;
	init_sdl_2(json, sdl);
	return (sdl);
}
