/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:20:37 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 04:31:46 by sleonia          ###   ########.fr       */
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
	SDL_SetWindowIcon(sdl->screen[0]->win, conv_sur_img);
	SDL_FreeSurface(conv_sur_img);
	ft_strdel(&icon);
}

static void			init_sdl_2(t_key_value *json, t_sdl *sdl)
{
	t_key_value		*assets;

	SDL_RenderSetScale(sdl->screen[0]->render, WIDTH, HEIGHT);
	SDL_UpdateTexture(sdl->screen[0]->texture, NULL,
					sdl->screen[0]->sur->pixels,
					WIDTH * sizeof(int));
	SDL_RenderClear(sdl->screen[0]->render);
	SDL_RenderCopy(sdl->screen[0]->render, sdl->screen[0]->texture, NULL, NULL);
	SDL_RenderPresent(sdl->screen[0]->render);
	assets = parse_assets(json, sdl);
	set_window_icon(assets, sdl);
	init_sdl_music(assets, sdl);
}

void				init_screen(t_screen *screen, char *title, SDL_Rect rect)
{
	if (!(screen->win = SDL_CreateWindow(title, rect.x,
		rect.y, rect.w, rect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP)))
		ft_error((char *)SDL_GetError());
	if (!(screen->render = SDL_CreateRenderer(screen->win, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_error((char *)SDL_GetError());
	if (!(screen->texture = SDL_CreateTexture(screen->render,
							SDL_PIXELFORMAT_ARGB8888,
							SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h)))
		ft_error((char *)SDL_GetError());
	if (!(screen->sur = SDL_CreateRGBSurface(0, rect.w, rect.h,
											32, 0, 0, 0, 0)))
		ft_error((char *)SDL_GetError());
	screen->win_id = SDL_GetWindowID(screen->win);
	screen->mouse_focus = 0;
	screen->keyboard_focus = 0;
	screen->full_screen = 0;
	screen->minimized = 0;
	screen->shown = 0;
}

t_sdl				*init_sdl(t_key_value *json)
{
	t_sdl			*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)))))
		ft_error(ERROR_INPUT);
	sdl->gui = init_gui();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		ft_error((char *)SDL_GetError());
	if (!(sdl->screen[0] = (t_screen *)ft_memalloc((sizeof(t_screen)))))
		ft_error(ERROR_INPUT);
	if (!(sdl->screen[1] = (t_screen *)ft_memalloc((sizeof(t_screen)))))
		ft_error(ERROR_INPUT);
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		ft_error((char *)SDL_GetError());
	init_screen(sdl->screen[0], "RT", (SDL_Rect){350, 200, WIDTH, HEIGHT});
	init_screen(sdl->screen[1], "ToolBar",
						(SDL_Rect){350 + WIDTH, 200, 500, HEIGHT});
	init_sdl_2(json, sdl);
	return (sdl);
}
