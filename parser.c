/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:44:57 by deladia           #+#    #+#             */
/*   Updated: 2019/10/26 20:45:00 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft/libft.h"

void			parser_error(char *str)
{
	ft_putstr(str);
	ft_putstr("\n");
	exit(1);
}

//t_cam	*create_camera()
//{
//	t_cam	*cam
//
//	return ()
//}
//
t_dictionary	*dictionary(void)
{
	t_dictionary	*dict;

	dict = (t_dictionary *)ft_memalloc(sizeof(t_dictionary));
	dict->object[0] = "camera:";
	dict->object[1] = "light:";
	dict->object[2] = "figure:";

	dict->camera_properties[0] = "position:";
	dict->camera_properties[1] = "cam_rotation:";

	dict->light_properties[0] = "type:";
	dict->light_properties[1] = "intensity:";
	dict->light_properties[2] = "position:";

	dict->light_type[0] = "point:";
	dict->light_type[1] = "ambient:";
	dict->light_type[2] = "derectional:";

	dict->figure_type[0] = "sphere:";
	dict->figure_type[1] = "cone:";
	dict->figure_type[2] = "cylinder:";
	dict->figure_type[3] = "plane:";

	dict->figure_properties[0] = "radius:";
	dict->figure_properties[1] = "color:";
	dict->figure_properties[2] = "specular:";
	dict->figure_properties[3] = "reflective:";
	dict->figure_properties[4] = "position:";
	dict->figure_properties[5] = "height:";

	dict->id[0] = "0:";
	dict->id[1] = "1:";
	dict->id[2] = "2:";
	dict->id[3] = "3:";
	dict->id[4] = "4:";
	dict->id[5] = "5:";
	dict->id[6] = "6:";
	dict->id[7] = "7:";
	dict->id[8] = "8:";
	dict->id[9] = "9:";

	dict->token[0] = '{';
	dict->token[1] = '}';
	dict->token[2] = ',';
	dict->token[3] = '.';
	dict->token[4] = '0';
	dict->token[5] = 'x';

	return (dict);
}

t_scene			*parse(t_scene *scene, char *file_sorce, t_dictionary *dict)
{

	return (scene);
}

int 			ft_open(t_scene *scene, char *file)
{
	ssize_t			fd;
	char 			*file_source;
	char 			*line;
	t_dictionary	*dict;

	if ((fd = open(file, O_RDONLY)) < 0)
		parser_error("Can't open file!");
	dict = dictionary();
//	get_next_line(fd, &line);
//	file_source = ft_strdup(line);
//	free(line);
//	while (get_next_line(fd, &line) > 0)
//	{
//		file_source = ft_strjoin(file_source, line);
//		file_source = ft_strjoin(file_source, "\n");
//		free(line);
//	}
	if (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, dict->object[0]))
		{
			free(line);
			get_next_line(fd, &line);
			if (ft_strchr(line, dict->token[0]))
			{
				free(line);
				get_next_line(fd, &line);
				if (ft_strstr(line, dict->camera_properties[0]))
				{
					if (ft_strchr(line, dict->token[0]))
					{

					}
				}
				else if (ft_strstr(line, dict->camera_properties[1]))
				{

				}
				else
					parser_error("Syntax error");
			}
			else
				parser_error("Syntax error");

		}
		else if (ft_strcmp(line, dict->object[1]))
		{

		}
		else if (ft_strcmp(line, dict->object[0]))
		{

		}
		else
			parser_error("Syntax error");
	}
	parse(scene, line, dict);
//	printf("%s", file_source);
	return (0);
}

//объекты -> свойства -> параметры
//для фигуо объект -> фигура -> свойста -> параметры
// разделитель , .
//токен float, int, 16-система, {}, ',', id(0, 1, 2...)
//токен для света тип света
//каждае ключевое слово в кавычки и двгать поинтер чтобы запомирнать позицию