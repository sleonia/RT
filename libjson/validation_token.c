/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:05:47 by deladia           #+#    #+#             */
/*   Updated: 2019/10/31 16:31:16 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				valid_token_1(t_token *token, t_dictionary *dict)
{
	(void)dict;
	if (token->type == Object || token->type == Subobject || token->type == Light_properties
	|| token->type == Camera_properties || token->type == Figure_properties || token->type == Light_type)
	{
		if (token->next->type == Separator)
			if (ft_strchr(token->next->value, dict->separator[4]))
				return (0);
	}
	else if (token->type == Hex)
	{
		if (token->next->type == Separator)
			if (ft_strchr(token->next->value, dict->separator[4]))
				return (0);
	}
	else if (token->type == Dec)
	{
		if (token->next->type == Separator)
		{
			if (ft_strchr(token->next->value, dict->separator[4]))
				return (0);
			else if (ft_strchr(token->next->value, dict->separator[2]))
				return (0);
			else if (ft_strchr(token->next->value, dict->separator[1]))
				return (0);
			else if (ft_strchr(token->next->value, dict->separator[3]))
				return (0);
		}
	}
	else if (token->type == Double_presition)
	{
		if (token->next->type == Separator)
		{
			if (ft_strchr(token->next->value, dict->separator[4]))
				return (0);
			else if (ft_strchr(token->next->value, dict->separator[1]))
				return (0);
		}
		if (token->next->type == Dec)
			return (0);
	}
	return (1);
}

int 			valid_token(t_token *token, t_dictionary *dict)
{
	if (token->type == Separator)
	{
		// "		обработано
		if (ft_strchr(token->value, dict->separator[4]))
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
			{
				if (ft_strchr(token->next->value, dict->separator[4]))
					return (0);
				else if (ft_strchr(token->next->value, dict->separator[3]))
					return (0);
			}
		}
		// :		обработано
		else if (ft_strchr(token->value, dict->separator[3]))
		{
			if (token->next->type == Separator)
			{
				if (ft_strchr(token->next->value, dict->separator[4]))
					return (0);
				else if (ft_strchr(token->next->value, dict->separator[0]))
					return (0);
			}
			else if (token->next->type == Dec)
				return (0);
			else if (token->next->type == Double_presition)
				return (0);
			else if (token->next->type == Hex)
				return (0);
		}
		// ,      	обработано
		else if (ft_strchr(token->value, dict->separator[2]))
		{
			if (token->next->type == Dec)
				return (0);
		}
		// }		обработано
		else if (ft_strchr(token->value, dict->separator[1]))
		{
			if (token->next->type == Separator)
			{
				if (ft_strchr(token->next->value, dict->separator[4]))
					return (0);
				else if (ft_strchr(token->next->value, dict->separator[1]))
					return (0);
			}
			else if (token->next->type == Dec)
				return (0);
		}
		// {  		обработано
		else if (ft_strchr(token->value, dict->separator[0]))
		{
			if (token->next->type == Separator)
			{
				if (ft_strchr(token->next->value, dict->separator[4]))
					return (0);
			}
			else if (token->next->type == Dec)
				return (0);
		}
	}
	return(valid_token_1(token, dict));
}

int				valiation_token_list(t_token *token, t_dictionary *dict)
{
	int 		ret;

	ret = 0;
	while (token)
	{
		printf("%s\n", token->value);
		if (!token->next)
			break ;
		if ((ret = valid_token(token, dict)) != 0)
			ft_error("Not valid token list");
		token = token->next;
	}
	return (0);
}

//валидность следующего токена сделана, теперь нужно длинную последовательность
//попробовать почитать про абстрактное синтаксическое дерево