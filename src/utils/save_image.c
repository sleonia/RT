/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 05:01:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/06 22:59:45 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_image_write.h"

// static char		*get_data(void)
// {
// 	char		*str_time;
// 	time_t		current_time;

// 	current_time = time(NULL);
// 	if (current_time == ((time_t)-1))
// 		exit(EXIT_FAILURE);
// 	str_time = ctime(&current_time);
// 	return (str_time);
// }

// static void		replace_symbs(char **str, char old_symb, char new_symb)
// {
// 	int			i;

// 	i = -1;
// 	while ((*str)[++i])
// 	{
// 		if ((*str)[i] == old_symb)
// 			(*str)[i] = new_symb;
// 		if (!(*str)[i + 1])
// 			(*str)[i] = '\0';
// 	}
// }

// static char		*make_screen_name(void)
// {
// 	char		*old_str_time;
// 	char		*new_str_time;

// 	if (!(old_str_time = get_data()))
// 		return (0);
// 	replace_symbs(&old_str_time, ':', '_');
// 	if (!(old_str_time = ft_strjoin(old_str_time, ".png")))
// 		return (0);
// 	if (!(new_str_time = ft_strjoin("./screenshots/Screen Shot at ",
// 		old_str_time)))
// 	{
// 		ft_strdel(&old_str_time);
// 		return (0);
// 	}
// 	ft_strdel(&old_str_time);
// 	return (new_str_time);
// }

void			save_image(t_sdl *sdl)
{
	// int			i;
	// int			k;
	// cl_int3		color;
	// char		*screen_name;
	// uint8_t		*rgb_image;

	// i = -1;
	// if (!(screen_name = make_screen_name())
	// 	|| !(rgb_image = ft_memalloc(WIDTH * HEIGHT * 3)))
	// 	return ;
	// while (++i < HEIGHT)
	// {
	// 	k = -1;
	// 	while (++k < WIDTH)
	// 	{
	// 		color = int_to_rgb(((int *)(sdl->sur->pixels))[k * WIDTH + i]);
	// 		rgb_image[3 * (k * WIDTH + i)] = (uint8_t)color.x;
	// 		rgb_image[3 * (k * WIDTH + i) + 1] = (uint8_t)color.y;
	// 		rgb_image[3 * (k * WIDTH + i) + 2] = (uint8_t)color.z;
	// 	}
	// }
	// stbi_write_png(screen_name, WIDTH, HEIGHT, 3, rgb_image, WIDTH * 3);
	// system("afplay /System/Library/Sounds/Pop.aiff");
	// ft_memdel((void **)&rgb_image);
	// ft_strdel(&screen_name);
}
