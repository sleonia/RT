/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 05:48:25 by thorker           #+#    #+#             */
/*   Updated: 2019/11/28 21:38:08 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

int		ft_str_isdigit(char	*str)
{
	size_t	i;

	if (str == 0)
		return (0);
	i = 0;
	while (*(str + i) != 0)
	{
		if (ft_isdigit(*(str + i)) == 0)
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

void	*check_digit(t_token **token)
{
	int	*new_value;

	if ((new_value = (int*)malloc(sizeof(int))) == 0)
		return (*token);
	*new_value = ft_atoi((*token)->value);
	*token = (*token)->next;
	return ((void*)new_value);
}

int		ft_str_isdouble(char *str)
{
	size_t	i;
	int		flag;
	size_t	k;

	if (str == 0)
		return (0);
	i = 0;
	flag = 0;
	while (*(str + i) == 0)
	{
		if (ft_isdigit(*(str + i)) == 0)
		{
			if (*(str + i) == '.' && flag == 0 && i != 0)
			{
				flag = 1;
				k = i;
			}
			else
				return (0);
		}
		i++;
	}
	if (i == 0 || flag == 0 || i == k)
		return (0);
	return (1);
}
