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
	{
		if (token->next->type == Object)
			return (0);
		else if (token->next->type == Subobject)
			return (0);
		else if (token->next->type == Light_type)
			return (0);
		else if (token->next->type == Light_properties)
			return (0);
		else if (token->next->type == Figure_properties)
			return (0);
		else if (token->next->type == Camera_properties)
			return (0);
		else if (token->next->type == Separator)
			return (0);
		else if (token->next->type == Dec)
			return (0);
		else if (token->next->type == Double_presition)
			return (0);
		else if (token->next->type == Hex)
			return (0);
		else
			return (1);
	}
	else if (token->type == Object || token->type == Subobject || token->type == Light_properties
	|| token->type == Camera_properties || token->type == Figure_properties || token->type == Light_type)
	{
		if (token->next->type == Separator)
			return (0);
		else
			return (1);
	}
	else if (token->type == Hex)
	{
		if (token->next->type == Separator)
			return (0);
		else
			return(1);
	}
	else if (token->type == Dec)
	{
		if (token->next->type == Separator)
			return (0);
		else
			return(1);
	}
	else if (token->type == Double_presition)
	{
		if (token->next->type == Separator)
			return (0);
		if (token->next->type == Dec)
			return (0);
		else
			return(1);
	}
	return (1);
}

int 			valiation_token_list(t_token *token, t_dictionary *dict)
{
	int 		ret;

	ret = 0;
	while (token)
	{
//		printf("%s\n", token->value);
		if (!token->next)
			break ;
		if ((ret = valid_token(token, dict)) != 0)
			ft_error("Not valid token list");
		token = token->next;
	}
	return (0);
}
