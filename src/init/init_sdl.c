/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:20:37 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 11:27:09 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			init_sdl_music(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
		ft_error((char *)SDL_GetError());
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	initAudio();
	sdl->volume = 0;
	// sdl->volume = 60;
	Mix_VolumeMusic(sdl->volume);
	if (!(sdl->music[0] = Mix_LoadMUS("./music/brain_perfect.mp3")))
		ft_error((char *)SDL_GetError());
	if (!(sdl->music[1] = Mix_LoadMUS("./music/far_out_on_my_own_feat_karra.mp3")))
		ft_error((char *)SDL_GetError());
	if (!(sdl->music[2] = Mix_LoadMUS("./music/lord_of_the_rings.mp3")))
		ft_error((char *)SDL_GetError());
	if (!(sdl->music[3] = Mix_LoadMUS("./music/seize_the_day.mp3")))
		ft_error((char *)SDL_GetError());
}

static void			set_window_icon(t_sdl *sdl)
{
	SDL_Surface		*sur_win;
	SDL_Surface		*sur_img;
	SDL_Surface		*conv_sur_img;

	if (!(sur_win = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0xFF000000,
										0x00FF0000, 0x0000FF00, 0x000000FF)))
		ft_error((char *)SDL_GetError());
	if (!(sur_img = IMG_Load("./textures/icon.jpg")))
		ft_error((char *)SDL_GetError());
	if (!(conv_sur_img = SDL_ConvertSurface(sur_img, sur_win->format, 0)))
		ft_error((char *)SDL_GetError());
	SDL_FreeSurface(sur_win);
	SDL_FreeSurface(sur_img);
	SDL_SetWindowIcon(sdl->window, conv_sur_img);
	SDL_FreeSurface(conv_sur_img);
}

t_sdl				*init_sdl(void)
{
	t_sdl			*sdl;

	sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		ft_error((char *)SDL_GetError());
	if (!(sdl->window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error((char *)SDL_GetError());
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_error((char *)SDL_GetError());
	if (!(sdl->texture = SDL_CreateTexture(sdl->render,
										SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIDTH, HEIGHT)))
		ft_error((char *)SDL_GetError());
	if (!(sdl->pixels = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		ft_error((char *)SDL_GetError());
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(int));
	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	set_window_icon(sdl);
	init_sdl_music(sdl);
	return (sdl);
}
