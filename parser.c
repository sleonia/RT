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
	dict->light_type[2] = "directional";

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

	dict->separator[0] = '{';
	dict->separator[1] = '}';
	dict->separator[2] = ',';
	dict->separator[3] = ':';
	dict->separator[4] = '"';
	return (dict);
}

int 			word_len(char *line, t_dictionary *dict)
{
	int 		len;
	int 		j;

	len = 0;
	while(line[len] != '\0' && line[len] != ' ' && line[len] != '\t')
	{
		len++;
		j = 5;
		while(j-- > 0)
		{
			if (line[len - 1] == dict->separator[j])
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

t_type			is_text(char *word, t_dictionary *dict)
{
	int 		i;

	i = 0;
	while(i < 3)
		if (!ft_strcmp(word, dict->object[i++]))
			return (Object);
	i = 0;
	while(i < 2)
		if (!ft_strcmp(word, dict->camera_properties[i++]))
			return (Camera_properties);
	i = 0;
	while(i < 3)
		if (!ft_strcmp(word, dict->light_properties[i++]))
			return (Light_properties);
	i = 0;
	while(i < 6)
		if (!ft_strcmp(word, dict->figure_properties[i++]))
			return (Figure_properties);
	i = 0;
	while(i < 3)
		if (!ft_strcmp(word, dict->light_type[i++]))
			return (Light_type);
	i = 0;
	while(i < 4)
		if (!ft_strcmp(word, dict->figure_type[i++]))
			return (Subobject);
	return (None);
}

t_type			is_separator(char *word, t_dictionary *dict)
{
	int 		i;

	i = 0;
	while(i < 5)
	{
		if (ft_strchr(word, dict->separator[i++]))
			return (Separator);
	}
	return (None);
}

t_type			is_number(char *word, t_dictionary *dict)
{
	int 		i;
	int 		len;

	i = 0;
	len = 0;
	if (word[0] == '-')
		len++;
	while(word[i] != '\0')
	{
		if (word[i] >= '0' && word[i] <= '9')
			len++;
		i++;
	}
	if (ft_strlen(word) == len)
		return (Oct);
	else if (ft_strlen(word) - len == 1 && word[1] == '.')
		return (Double_presition);
	else if (word[0] == '0' && word[1] == 'x')
		return (Hex);
	return (None);
}

t_token			*init_token(char *word, t_token *token, t_type type)
{
	if (token == NULL)
	{
		token->value = ft_strdup(word);
		token->type = type;
	}
	else
	{
		if ((token->next = (t_token *)ft_memalloc(sizeof(t_token))) == NULL)
			ft_error("Memory not allocated (for token)");
		token = token->next;
		token->value = ft_strdup(word);
		token->type = type;
	}
	return (token);
}

t_token			*create_token(char *word, t_dictionary *dict, t_token *token)
{
	t_type		type;

	if ((type = is_text(word, dict)) != None)
		token = init_token(word, token, type);
	else if ((type = is_separator(word, dict)) != None)
		token = init_token(word, token, type);
	else if ((type = is_number(word, dict)) != None)
		token = init_token(word, token, type);
	else
		ft_error("Non-existent token type");
//	printf("%d\n", type);
	return (token);
}

t_token			*parse(char *line, t_dictionary *dict, t_token *token)
{
	char 	*word;

	while(*line != '\0')
	{
		word = create_word(&line, dict);
		token = create_token(word, dict, token);
//		printf("%s\n", word);
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
	if (!(token_head = (t_token *)ft_memalloc(sizeof(t_token))))
		ft_error("Memory not allocated (for token)");
	token_tmp = token_head;
	while (get_next_line(fd, &line) > 0)
	{
		token_tmp = parse(line, dict, token_tmp);
		free(line);
	}
	while (token_head)
	{
		printf("%s\n", token_head->value);
		token_head = token_head->next;
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



//написать стандарт документацию
//строка двойная ковычка
//использовать буквы как ключевые слова
//придумать как избавиться от валидных повторов
//подменять Hex на Id ????удобно ли