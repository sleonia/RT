/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:37:18 by thorker           #+#    #+#             */
/*   Updated: 2020/01/17 18:38:08 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

/*
** Проверяет возможные типы переменных и вызывает соответсвующие функции
*/

void	*check_value(t_token **token, t_type *type)
{
	void	*new_value;

	new_value = 0;
	if (ft_str_isdigit((*token)->value) != 0)
	{
		if ((new_value = make_digit(token)) != *token)
			*type = Dec;
	}
	else if (ft_token_isstr(token) != 0)
	{
		if ((new_value = make_string((*token)->value)) == 0)
			return (0);
		*type = String;
		*token = (*token)->next->next;
	}
	else if (ft_str_isdouble((*token)->value) != 0)
	{
		if ((new_value = make_double(token)) != *token)
			*type = Doub;
	}
	else if ((new_value = make_object(token)) != *token)
		*type = Object;
	else
		ft_putendl((*token)->value);
	return (new_value);
}
//соединить ли is digit и make digit
