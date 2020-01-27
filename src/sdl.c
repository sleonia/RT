/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:43:04 by deladia           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:02 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_error(char *str)
{
	ft_putstr(str);
	ft_putendl(SDL_GetError());
	exit(1);
}

void		ft_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

int 		sdl_update(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels,
					  WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	return (0);
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

static void			init_sdl_music(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
		ft_error((char *)SDL_GetError());
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	sdl->volume = 60;
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

/*
** 	Бесконечный цикл реагирующий на нажатие клавишь и обновляющий после этого текстуру
*/
int			sdl_control(t_sdl *sdl, t_scene *scene, t_cl *cl)
{
	char	quit;

	quit = 0;
	sdl_update(sdl);
	while (!quit)
	{
		while (SDL_PollEvent(&sdl->event))
		{
			if (sdl->event.type == SDL_QUIT)
				quit = 1;
			//ивент нажата кнопка
			if (sdl->event.type == SDL_KEYDOWN)
			{
				//сравниваем с тем что нажато и делаем то что нужно
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_W)
				{
					scene->cam.pos.s[2] += 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_S)
				{
					scene->cam.pos.s[2] -= 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_A)
				{
					scene->cam.pos.s[0] -= 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_D)
				{
					scene->cam.pos.s[0]+= 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_R)
				{
					scene->cam.pos.s[1] += 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_F)
				{
					scene->cam.pos.s[1] -= 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Z)
				{
					scene->cam.phi += 0.1;
					if (scene->cam.phi > (float)M_PI - 0.00001f)
						scene->cam.phi -= 2 * (float)M_PI;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_X)
				{
					scene->cam.phi -= 0.1;
					if (scene->cam.phi < -(float)M_PI + 0.00001f)
						scene->cam.phi += -2 * (float)M_PI;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Q)
				{
					if ((scene->cam.tetta) - 0.1 >= 0.00001f)
						scene->cam.tetta -= 0.1;
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_E)
				{
					if ((scene->cam.tetta) + 0.1 <= (float)M_PI + 0.00001f)
						scene->cam.tetta += 0.1;
				}
				calc_screen(&scene->cam);
				set_arg(cl, sdl, scene);
				sdl_update(sdl);
			}
		}
	}
	//Уборка мусора
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit(0);
	return (0);
}

int			sdl_init(t_sdl *sdl)
{
	//Инициальзация нужных подсистем
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		sdl_error("SDL_Init Error: ");
	//Создание окна (название, х, у, ширина, высота, флаги)
	if ((sdl->window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		sdl_error("SDL_CreateWindow Error: ");
	//Создание рендера для рисования (окно, индекс драйвера(-1, тогда сам найдет нужный), флаги на тип рендера)
	if ((sdl->render = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED
	| SDL_RENDERER_PRESENTVSYNC)) == NULL)
		sdl_error("SDL_CreateRenderer Error: ");
	//Cоздание пустой текстуры в формате ARGB8888
	if ((sdl->texture = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)) == NULL)
		sdl_error("SDL_CreateTextureFromSurface Error: ");
	//Создание массива цветов
	if (!(sdl->pixels = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		ft_error("Error pixels memory allocation");
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(int));
	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	set_window_icon(sdl);
	init_sdl_music(sdl);
	return (0);
}
