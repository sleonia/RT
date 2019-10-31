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

/*
** 		Парсит line по ключевым словам и кладет в односвязный список token
** 		возвращает указатель на последний добавленный token
*/

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

/*
** 		Открывает json создает указатель на первый токен token_head
** 		Читает гнлом построчно и каждую строку сразу отправляет в parse
** 		Затем вызывает проверку на валидность последовательности токенов
 */

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
	valiation_token_list(token_head, dict);

//	printf("%s", file_source);
	return (0);
}

//int 	main(void)
//{
//	t_scene		*scene;
//
//	scene = NULL;
//	ft_open(scene, "../param.json");
//	return (0);
//}
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