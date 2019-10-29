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
	dict->separatorn[5] = '"';
	return (dict);
}

//char 			*word(char *file_sorce)
//{
//	char		*buf;
//	int 		i;
//
//	i = 0;
//	if (*file_sorce++ == '"')
//	{
//		while (*file_sorce != '"')
//		{
//			buf[i] = *file_sorce;
//			i++;
//			file_sorce++;
//		}
//	}
//	return (buf);
//}

int 			word_len(char *line, t_dictionary *dict)
{
	int 		len;
	int 		j;

	len = 0;
	while(line[len] != '\0' && line[len] != ' ' && line[len] != '\t')
	{
		len++;
		j = 6;
		while(j-- > 0)
		{
			if (line[len - 1] == dict->separatorn[j])
				return (len == 1 ? len : len - 1);
		}
	}
	return (len);
}

char 			*create_word(char **line, t_dictionary *dict)
{
	char 		*word;
	int 		i;
	int 		len;

	i = 0;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	len = word_len(*line, dict);
	if (!(word = (char *)ft_memalloc(sizeof(char) * len + 1)))
		ft_error("Memory not allocated (for word)");
	while(len-- > 0)
	{
		word[i] = **line;
		i++;
		(*line)++;
	}
	word[i] = '\0';
	return (word);
}

t_token			*parse(char *line, t_dictionary *dict, t_token *token)
{
	char 	*word;

	while(*line != '\0')
	{
		word = create_word(&line, dict);
		printf("%s\n", word);
		free(word);
//		line++;
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
		ft_error("Can't open file!");
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

int 	main(void)
{
	t_scene		*scene;

	scene = NULL;
	ft_open(scene, "../param.json");
	return (0);
}
//объекты -> свойства -> параметры
//для фигуо объект -> фигура -> свойста -> параметры
// разделитель , .
//токен float, int, 16-система, {}, ',', id(0, 1, 2...)
//токен для света тип света
//каждае ключевое слово в кавычки и двигать поинтер чтобы запомирнать позицию
//чекать до сепаратора {} ' ' , :