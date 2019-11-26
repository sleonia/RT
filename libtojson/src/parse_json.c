/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:44:06 by thorker           #+#    #+#             */
/*   Updated: 2019/11/26 16:46:45 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

t_key_value     *parse_json(char* file_name)
{
	t_key_value     *tmp;
	t_token         *token;
	t_token         *head_token;

	tmp = NULL;
	token = ft_open(file_name);
	head_token = token;
	if (token == 0)
		return (0);
	if (ft_strcmp(token->value, "{") == 0)
		tmp = check_object(&token);
	else
	{
		ft_putendl(token->value);
		return (0);
	}
	if ((t_token*)tmp == token)
	{
		ft_error("токен равен тмп");
	}
	while (head_token != 0)
	{
		token = head_token->next;
		free(head_token->value);
		free(head_token);
		head_token = token;
	}
	return (tmp);
}
