/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:05:47 by deladia           #+#    #+#             */
/*   Updated: 2019/10/30 16:05:49 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int 			valid_token(t_token *token, t_dictionary *dict)
{
	if (token->type == Separator)
		if (ft_strchr(token->value, dict->separator[4]))
		{

		}
	return (0);
}

int 			valiation_token_list(t_token *token, t_dictionary *dict)
{
	int 		ret;

	ret = 0;
	while (token)
	{
		ret = valid_token(token, dict);
		printf("%s\n", token->value);
		token = token->next;
	}
	return (0);
}
