/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:55:14 by delalia           #+#    #+#             */
/*   Updated: 2019/11/07 22:50:27 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"
#include "rtv1.h"
//добавить функцию добавления имени и проверки на валидность

int				add_name(t_key_value *for_re, t_token **token)
{
	char	**new;
	size_t	i;
	size_t	k;
	t_type	type;
	void	*new_value;

	i = 0;
	while (*(for_re->key + i) != 0)
		i++;
	new = (char**)malloc(sizeof(char*) * (i + 2));
	k = 0;
	while (k <= i)
	{
		*(new + k) = ft_strdup(*(for_re->key + k));
		ft_strdel(for_re->key + k);
		k++;
	}
	*(new + k) = ft_strdup((*token)->value);
	*(new + k + 1) = 0;
	*token = (*token)->next;
	if (*token == 0 || ft_strcmp((*token)->value, "\"") != 0 ||
			(*token = (*token->next)) == 0 || ft_strcmp((*token)->value, ":") != 0
			|| (*token = (*token->next)) == 0)
	{
		k = 0;
		while (k < i + 2)
		{
			ft_strdel(new + k);
			k++;
		}
		free(new);
		return (-1);
	}
	if (ft_strcmp((*token)->value, "[") == 0)
	{
		if ((new_value = add_value_array(token, &type)) == *token)
		{
			k = 0;
			while (k < i + 2)
			{
				ft_strdel(new + k);
				k++;
			}
			free(new);
			return (-1);
		}
	}
	if (ft_strcmp((*token)->value, "{") == 0)
	{
		if ((new_value = check_object(token, &type)) == *token)
		{
			k = 0;
			while (k < i + 2)
			{
				ft_strdel(new + k);
				k++;
			}
			free(new);
			return (-1);
		}
	}
	//начать с проверки string
	free(for_re->key);
	for_re->key = new;
		
}

t_key_value		*check_object(t_token **token, t_type *type)
{
	t_key_value		*for_re;

	if ((*token)->next != 0 && ft_strcmp((*token)->next->value, "}") != 0)
		return (0);
	else
	{
		for_re = (t_key_value*)malloc(sizeof(t_key_value));
		for_re->key = (char**)malloc(sizeof(char*));
		*(for_re->key) = 0;
		for_re->value = (void**)malloc(sizeof(void*));
		*(for_re->value) = 0;
		for_re->type = (char**)malloc(sizeof(char*));
		*(for_re->type) = 0;
	}
	*token = (*token)->next;
	while (*token != 0)
	{
		//добавить проерку ","
		if (ft_strcmp((*token)->value, "}") == 0)
			return (for_re);
		if (ft_strcmp((*token)->value, "\"") == 0)
		{
			*token = (*token)->next;
			if (add_name(for_re, token) != 0)
				return (fr_return(token
		}
	}
	return (*token);
}

//проверить "{" в самом начале (до этой функции)
//считается ли {} null или нет
//что делать если   token == 0
