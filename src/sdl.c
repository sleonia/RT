/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:43:04 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 13:57:53 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			sdl_update(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels,
		WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	return (0);
}

void		sdl_control_1(t_sdl *sdl, t_scene *scene)
{
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_W)
	{
		scene->cam->position.z += 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_S)
	{
		scene->cam->position.z -= 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_A)
	{
		scene->cam->position.x -= 0.1;
		trace_start(sdl, scene);
	}
	if (sdl->event.key.keysym.scancode == SDL_SCANCODE_D)
	{
		scene->cam->position.x += 0.1;
		trace_start(sdl, scene);
	}
}

void		sdl_control_0(t_sdl *sdl, t_scene *scene)
{
	sdl_control_1(sdl, scene);
	sdl_control_2(sdl, scene);
	sdl_control_3(sdl, scene);
	sdl_control_4(sdl, scene);
	sdl_control_5(sdl, scene);
	sdl_control_6(sdl, scene);
	sdl_update(sdl);
}

/*
** 	Бесконечный цикл реагирующий на нажатие клавишь
** и обновляющий после этого текстуру
*/

int			sdl_control(t_sdl *sdl, t_scene *scene)
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
			if (sdl->event.type == SDL_KEYDOWN)
			{
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
				sdl_control_0(sdl, scene);
			}
		}
	}
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit(0);
}

int			sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		sdl_error("SDL_Init Error: ");
	if ((sdl->window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		sdl_error("SDL_CreateWindow Error: ");
	if ((sdl->render = SDL_CreateRenderer(sdl->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
		sdl_error("SDL_CreateRenderer Error: ");
	if ((sdl->texture = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)) == NULL)
		sdl_error("SDL_CreateTextureFromSurface Error: ");
	if (!(sdl->pixels = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		ft_error("Error pixels memory allocation");
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(int));
	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	return (0);
}
