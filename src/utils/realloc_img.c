/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 01:35:40 by thorker           #+#    #+#             */
/*   Updated: 2020/01/30 15:47:08 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
**	Создает новый массив текстур
**	копирует старый массив
**	помещает новые значения
*/

static int	*new_texture(t_scene *scene, SDL_Surface *image)
{
	int		*texture;
	size_t	image_length;

	image_length = image->w * image->h;
	if ((texture = (int*)malloc(sizeof(int) *
					(scene->texture_length + image_length))) == 0)
		return (0);
	ft_memcpy((void*)texture, (void*)scene->texture,
			sizeof(int) * scene->texture_length);
	ft_memcpy((void*)texture + (scene->texture_length) * sizeof(int),
			(void*)image->pixels, sizeof(int) * image_length);
	return (texture);
}

/*
**	Создает новый массив для параметров тексур
**	копирует старый массив
**	помещает новые значения
*/

static int	*new_texture_param(t_scene *scene, SDL_Surface *image)
{
	int	*texture_param;

	if ((texture_param = (int*)malloc(sizeof(int) *
					(3 * (scene->texture_cnt + 1)))) == 0)
		return (0);
	ft_memcpy((void*)texture_param, (void*)scene->texture_param,
			3 * sizeof(int) * scene->texture_cnt);
	texture_param[3 * scene->texture_cnt] = scene->texture_length;
	texture_param[3 * scene->texture_cnt + 1] = image->w;
	texture_param[3 * scene->texture_cnt + 2] = image->h;
	return (texture_param);
}

/*
**	Открывает изображение
**	перевыделяет память для массива текстур и параметр текстур
**	задает новые значения.
*/

int			realloc_img(t_scene *scene, char *file_name)
{
	SDL_Surface *image;
	int			*texture;
	int			*texture_param;

	if (file_name == 0 || (image = IMG_Load(file_name)) == 0)
		return (CANT_OPEN_IMAGE);
	if ((texture = new_texture(scene, image)) == 0 |
			(texture_param = new_texture_param(scene, image)) == 0)
	{
		if (texture != 0)
			ft_memdel((void**)&texture);
		if (texture_param != 0)
			ft_memdel((void*)&texture_param);
		SDL_FreeSurface(image);
		return (MALLOC_ERROR);
	}
	if (scene->texture_cnt++ != 0)
		ft_memdel((void*)&(scene->texture_param));
	if (scene->texture_length != 0)
		ft_memdel((void*)&(scene->texture));
	scene->texture = texture;
	scene->texture_param = texture_param;
	scene->texture_length += image->w * image->h;
	SDL_FreeSurface(image);
	return (0);
}
