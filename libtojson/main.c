/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:54:41 by deladia           #+#    #+#             */
/*   Updated: 2019/11/11 10:44:47 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

void	free_token(t_token **token)
{
	t_token		*tmp;

	tmp = *token;
	while(tmp)
	{
		*token = tmp;
		if (tmp->next)
			tmp = tmp->next;
		free((*token)->value);
		free(token);
	}
}

int		main(void)
{
	t_key_value		*tmp;
	t_token			*token;

	tmp = NULL;
	token = ft_open("../../test.json");
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
	ft_print(tmp);
	//возвращается указатель на последний token
//	free_token(&token);
	return (0);
}
