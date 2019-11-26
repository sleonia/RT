/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:55:14 by delalia           #+#    #+#             */
/*   Updated: 2019/11/26 15:12:24 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

int				realloc_key_value(t_key_value *for_re, char* new_key, void *new_value, t_type new_type)
{
	size_t	i;
	char	**new_key_array;
	void	**new_value_array;
	t_type	*new_type_array;
	size_t	k;

	i = 0;
	while (*(for_re->key + i) != 0)
		i++;
	if ((new_key_array = (char**)malloc(sizeof(char*) * (i + 2))) == 0)
		return (0);
	if ((new_value_array = (void**)malloc(sizeof(void*) * (i + 1))) == 0)
	{
		free(new_key_array);
		return (0);
	}
	if ((new_type_array = (t_type*)malloc(sizeof(t_type) * (i + 1))) == 0)
	{
		free(new_key_array);
		free(new_value_array);
		return (0);
	}
	k = 0;
	while (k < i)
	{
		*(new_key_array + k) = *(for_re->key + k);
		*(new_value_array + k) = *(for_re->value + k);
		*(new_type_array + k) = *(for_re->type + k);
		k++;
	}
	*(new_key_array + k) = new_key;
	*(new_key_array + k + 1) = 0;
	*(new_value_array + k) = new_value;
	*(new_type_array + k) = new_type;
	free(for_re->key);
	free(for_re->value);
	if (for_re->type != 0)
		free(for_re->type);
	for_re->key = new_key_array;
	for_re->value = new_value_array;
	for_re->type = new_type_array;
	return (1);
}

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

//проверить "{" и на  в самом начале (до этой функции)
//считается ли {} null или нет
//что делать если   token == 0
