/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:55:14 by delalia           #+#    #+#             */
/*   Updated: 2019/11/26 19:28:12 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"
/*
 *	Функция которая проверяет имя и вызывает функцию для обработки значения
 */
int				check_value_and_name(t_key_value *for_re, t_token **token)
{
	char	*new_key;
	void	*new_value;
	t_type	new_type;

	new_type = 0;
	if ((*token = (*token)->next) == 0)
		return (0);
	if ((new_key = ft_strdup((*token)->value)) == 0)
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
 *	функция, которая проверяет валидность объектов
 */

void		*check_object(t_token **token)
{
	t_key_value		*for_re;

	//разделить проверки
	if ((*token)->next != 0 && ft_strcmp(((*token)->next)->value, "}") == 0)
		return (0);
	else
	{
		for_re = (t_key_value*)malloc(sizeof(t_key_value));
		for_re->key = (char**)malloc(sizeof(char*));
		*(for_re->key) = 0;
		for_re->value = (void**)malloc(sizeof(void*));
		*(for_re->value) = 0;
		for_re->type = 0;
	}
	*token = (*token)->next;
	while (*token != 0)
	{
		if (ft_strcmp((*token)->value, "\"") == 0)
		{
			if (check_value_and_name(for_re, token) == 0)
			{
				ft_return(&for_re);
				return (*token);
			}
		}
		if (ft_strcmp((*token)->value, ",") == 0)
			*token = (*token)->next;
		else if (ft_strcmp((*token)->value, "}") == 0)
			return (for_re);
		else
		{
			ft_return(&for_re);
			return (*token);
		}
	}
	return (*token);
}
//что делать если   token == 0
