/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:55:14 by delalia           #+#    #+#             */
/*   Updated: 2019/11/28 22:31:17 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

char				*create_string(char *str)
{
	char	*new_key;
	size_t	k;
	size_t	i;

	k = 0;
	i = 0;
	while (*(str + k) != 0)
	{
		if (*(str + k) != '\\')
			i++;
		else if (*(str + ++k) == 0)
			return (0);
		k++;
	}
	if ((new_key = ft_strnew(i)) == 0)
		return (0);
	i = 0;
	k = 0;
	while (*(str + k) != 0)
	{
		if (*(str + k) == '\\')
			k++;
		*(new_key + i++) = *(str + k++);
	}
	return (new_key);
}

char				*check_key(t_token **token)
{
	char	*new_key;

	if ((*token = (*token)->next) == 0)
		return (0);
	if ((new_key = create_string((*token)->value)) == 0)
		return (0);
	if ((*token = (*token)->next) == 0 ||
			ft_strcmp((*token)->value, "\"") != 0 ||
			(*token = (*token)->next) == 0 ||
			ft_strcmp((*token)->value, ":") != 0 ||
			(*token = (*token)->next) == 0)
	{
		ft_strdel(&new_key);
		return (0);
	}
	return (new_key);
}

/*
**	Функция которая проверяет имя и вызывает функцию для обработки значения
*/

int					check_value_and_name(t_key_value *for_re, t_token **token)
{
	char	*new_key;
	void	*new_value;
	t_type	new_type;

	new_type = 0;
	if ((new_key = check_key(token)) == 0)
		return (0);
	if (ft_str_isdigit((*token)->value) != 0)
	{
		if ((new_value = check_digit(token)) != *token)
			new_type = Dec;
	}
	if (new_type == 0)
	{
		ft_strdel(&new_key);
		return (0);
	}
	else if (realloc_key_value(for_re, new_key, new_value, new_type) == 0)
	{
		ft_strdel(&new_key);
		free(new_value);
		return (0);
	}
	return (1);
}

/*
** функция в которой создается пустая структура
*/

static t_key_value	*create_empty_struct(void)
{
	t_key_value	*for_re;

	if ((for_re = (t_key_value*)malloc(sizeof(t_key_value))) == 0)
		return (0);
	if ((for_re->key = (char**)malloc(sizeof(char*))) == 0)
	{
		free(for_re);
		return (0);
	}
	if ((for_re->value = (void**)malloc(sizeof(void*))) == 0)
	{
		free(for_re->key);
		free(for_re);
		return (0);
	}
	*(for_re->key) = 0;
	*(for_re->value) = 0;
	for_re->type = 0;
	return (for_re);
}

/*
**	функция, которая проверяет валидность объектов
*/

void				*check_object(t_token **token)
{
	t_key_value		*for_re;

	if ((*token = (*token)->next) != 0 && ft_strcmp((*token)->value, "}") == 0)
		return (0);
	else if ((for_re = create_empty_struct()) == 0)
		return (*token);
	while (*token != 0)
	{
		if (ft_strcmp((*token)->value, "\"") == 0)
		{
			if (check_value_and_name(for_re, token) == 0)
				break ;
			if (ft_strcmp((*token)->value, ",") == 0)
			{
				*token = (*token)->next;
				continue;
			}
		}
		if (ft_strcmp((*token)->value, "}") == 0)
			return (for_re);
		break ;
	}
	ft_return(&for_re);
	return (*token);
}
