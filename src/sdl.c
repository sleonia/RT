/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:43:04 by deladia           #+#    #+#             */
/*   Updated: 2019/10/31 16:48:56 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sdl_error(char *str)
{
	ft_putstr(str);
	ft_putstr(SDL_GetError());
	write(1, "\n", 1);
	exit(1);
}

void		ft_error(char *str)
{
	ft_putstr(str);
	write(1, "\n", 1);
	exit(1);
}

/*void		ft_free(t_rtv1 *rtv1)
{
	free(rtv1->sdl);
	free(rtv1->scene->cam);
	free(rtv1->scene->view);
	free(rtv1->scene);
	free(rtv1);
}*/

int 		sdl_update(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels,
					  WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	return (0);
}

/*
** 	Бесконечный цикл реагирующий на нажатие клавишь и обновляющий после этого текстуру
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
			//ивент нажата кнопка
			if (sdl->event.type == SDL_KEYDOWN)
			{
				//сравниваем с тем что нажато и делаем то что нужно
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
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
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_R)
				{
					scene->cam->position.y += 0.1;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_F)
				{
					scene->cam->position.y -= 0.1;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Z && scene->cam->a <= 90)
				{
					scene->cam->a += 10;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_X && scene->cam->a >= -90)
				{
					scene->cam->a -= 10;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_Q && scene->cam->b >= -90)
				{
					scene->cam->b -= 10;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_E && scene->cam->b <= 90)
				{
					scene->cam->b += 10;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_P)
				{
					if (!scene->off->point)
						scene->off->point = 1;
					else
						scene->off->point = 0;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_I)
				{
					if (!scene->off->ambient)
						scene->off->ambient = 1;
					else
						scene->off->ambient = 0;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_O)
				{
					if (!scene->off->directional)
						scene->off->directional = 1;
					else
						scene->off->directional = 0;
					trace_start(sdl, scene);
				}
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_U)
				{
					if (!scene->off->reflect)
						scene->off->reflect = 1;
					else
						scene->off->reflect = 0;
					trace_start(sdl, scene);
				}
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
	return (0);
}
