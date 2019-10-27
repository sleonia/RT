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
	dict->object[0] = "camera";
	dict->object[1] = "light";
	dict->object[2] = "figure";

	dict->camera_properties[0] = "position";
	dict->camera_properties[1] = "cam_rotation";

	dict->light_properties[0] = "type";
	dict->light_properties[1] = "intensity";
	dict->light_properties[2] = "position";

	dict->light_type[0] = "point";
	dict->light_type[1] = "ambient";
	dict->light_type[2] = "derectional";

	dict->figure_type[0] = "sphere";
	dict->figure_type[1] = "cone";
	dict->figure_type[2] = "cylinder";
	dict->figure_type[3] = "plane";

	dict->figure_properties[0] = "radius";
	dict->figure_properties[1] = "color";
	dict->figure_properties[2] = "specular";
	dict->figure_properties[3] = "reflective";
	dict->figure_properties[4] = "position:";
	dict->figure_properties[5] = "height";

	dict->separatorn[0] = '{';
	dict->separatorn[1] = '}';
	dict->separatorn[2] = ',';
	dict->separatorn[3] = '.';
	dict->separatorn[4] = ':';
	return (dict);
}

char 			*word(char *file_sorce)
{
	char		*buf;
	int 		i;

	i = 0;
	if (*file_sorce++ == '"')
	{
		while (*file_sorce != '"')
		{
			buf[i] = *file_sorce;
			i++;
			file_sorce++;
		}
	}
	return (buf);
}

int 			word_len(char *line)
{
	int 		len;
	int 		i;

	i = 0;
	while(line[i])
	return (len);
}

t_token			*parse(char *line, t_dictionary *dict, t_token *token)
{
	int 	i;

	i = 0;
	while(*line != '\0')
	{

	}
	return (token);
}

int 			ft_open(t_scene *scene, char *file)
{
	ssize_t			fd;
	char 			*line;
	t_dictionary	*dict;
	t_token			*token_head;
	t_token			*token_tmp;


	if ((fd = open(file, O_RDONLY)) < 0)
		parser_error("Can't open file!");
	dict = dictionary();
	token_head = (t_token *)ft_memalloc(sizeof(t_token));
	token_tmp = token_head;
	while (get_next_line(fd, &line) > 0)
	{
		token_tmp = parse(line, dict, token_tmp);
		free(line);
	}

//	printf("%s", file_source);
	return (0);
}

//объекты -> свойства -> параметры
//для фигуо объект -> фигура -> свойста -> параметры
// разделитель , .
//токен float, int, 16-система, {}, ',', id(0, 1, 2...)
//токен для света тип света
//каждае ключевое слово в кавычки и двгать поинтер чтобы запомирнать позицию
//чекать до сепаратора {} ' ' , :