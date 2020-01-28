/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 03:30:49 by deladia           #+#    #+#             */
/*   Updated: 2020/01/28 13:24:46 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// int					*fill_texture_for_object(char *texture_path,
// 											int *texture_pixels,
// 											int *texture_param)
// {
// 	SDL_Surface		*image;
// 	SDL_Surface		*tmp;
// 	int				*texture_pixels;

// 	image = SDL_LoadBMP(texture_path);
// 	if (image == NULL)
// 	{
// 		ft_putendl(SDL_GetError());
// 		return (NULL);
// 	}
// 	tmp = image;
// 	image = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
// 	if (texture_pixels == NULL)
// 	{
// 		texture_pixels = (int *)ft_memalloc(sizeof(int) * image->w * image->h);
// 		texture_param = (int *)ft_memalloc(sizeof(int) * 3);
// 		ft_memcpy(texture_pixels, (int *)image->pixels,
// 				image->w * image->h * sizeof(int));
// 		texture_param[0] = -1;
// 		texture_param[1] = image->w;
// 		texture_param[2] = image->h;
// 	}
// 	SDL_FreeSurface(image);
// 	SDL_FreeSurface(tmp);
// 	return (0);
// }
