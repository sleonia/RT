/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 05:48:25 by thorker           #+#    #+#             */
/*   Updated: 2020/01/18 17:25:15 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

void	*make_double(t_token **token)
{
	double *new_value;

	if ((new_value = (double*)malloc(sizeof(double))) == 0)
		return (*token);
	*new_value = ft_atof((*token)->value);
	*token = (*token)->next;
	return ((void*)new_value);
}

/*
** создает число и двигает токен
*/

void	*make_digit(t_token **token)
{
	int	*new_value;

	if ((new_value = (int*)malloc(sizeof(int))) == 0)
		return (*token);
	*new_value = ft_atoi((*token)->value);
	*token = (*token)->next;
	return ((void*)new_value);
}

/*
** создает строку и убирает знаки экранирования
*/

char	*make_string(char *str)
{
	char	*new_key;
	size_t	k;
	size_t	i;

	k = 0;
	i = 0;
	while (*(str + k) != 0)
	{
		if (*(str + k) == '\\' && *(str + ++k) == 0)
			return (0);
		k++;
		i++;
	}
	if ((new_key = ft_strnew(i)) == 0)
		return (0);
	i = 0;
	k = 0;
	while (*(str + k) != 0)
	{
		if (*(str + k) == '\\')
			k++;
		*(new_key + i++) = *(str + k++);
	}
	return (new_key);
}

/*
**	создает массив
*/
//добавить отчистку при ошибке
void	*make_array(t_token	**token)
{
	t_array	*array;
	t_type	type;
	void	*value;

	if ((*token)->next == 0 || (array = (t_array*)malloc(sizeof(t_array))) == 0)
		return (*token);
	*token = (*token)->next;
	array->length = 0;
	while (*token != 0)
	{
		type = 0;
		value = check_value(token, &type);
		if (type == 0 || *token == 0)
			break ;
		if (realloc_array(array, value, type) == 0)
			break ;
		if (ft_strcmp((*token)->value, ",") == 0)
		{
			*token = (*token)->next;
			continue;
		}
		if (ft_strcmp((*token)->value, "]") == 0)
		{
			*token = (*token)->next;
			return (array);
		}
		break ;
	}
	//free(array) всего массива.
	return (*token);
}











