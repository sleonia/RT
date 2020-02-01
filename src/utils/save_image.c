/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 05:01:29 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/01 05:06:54 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// char			*get_data()
// {
// 	time_t current_time;
// 	char* c_time_string;

// 	/* Obtain current time. */
// 	current_time = time(NULL);
// 	if (current_time == ((time_t)-1))
// 	{
// 		(void) fprintf(stderr, "Failure to obtain the current time.\n");
// 		exit(EXIT_FAILURE);
//     }
//     /* Convert to local time format. */
// 	c_time_string = ctime(&current_time);
// 	if (c_time_string == NULL)
//     {
//         (void) fprintf(stderr, "Failure to convert the current time.\n");
//         exit(EXIT_FAILURE);
//     }

//     /* Print to stdout. ctime() has already added a terminating newline character. */
//     (void) printf("Current time is %s", c_time_string);
//     exit(EXIT_SUCCESS);
// }

	
// }

// void			save_image(t_sdl *sdl)
// {
// 	uint8_t		*rgb_image;
// 	cl_int3		color;
// 	int			i;
// 	int			k;

// 	i = -1;
// 	if (!(rgb_image = ft_memalloc(WIDTH * HEIGHT * 3)))
// 		ft_error("MALLOC_ERROR");
// 	while (++i < HEIGHT)
// 	{
// 		k = -1;
// 		while (++k < WIDTH)
// 		{
// 			color = int_to_rgb(sdl->pixels[k * WIDTH + i]);
// 			rgb_image[3 * (k * WIDTH + i)] = (uint8_t)color.x;
// 			rgb_image[3 * (k * WIDTH + i) + 1] = (uint8_t)color.y;
// 			rgb_image[3 * (k * WIDTH + i) + 2] = (uint8_t)color.z;
// 		}
// 	}
// 	stbi_write_png("sky2.png", WIDTH, HEIGHT, 3, rgb_image, WIDTH * 3);
// }
