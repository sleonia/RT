/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:55:14 by delalia           #+#    #+#             */
/*   Updated: 2019/11/06 21:34:24 by thorker          ###   ########.fr       */
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

}

t_key_value		*check_object(t_token **token)
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
		if (ft_strcmp((*token)->value, "}") == 0)
			return (for_re);
		if (ft_strcmp((*token)->value, "\"") == 0)
		{
			*token = (*token)->next;
			if (add_name(for_re, token) != 0)
				return (fr_return(token
		}
	}
	//добавить функцию цистки всей структуры
	return (*token);
}

//проверить "{" в самом начале (до этой функции)
//считается ли {} null или нет
//что делать если   token == 0
