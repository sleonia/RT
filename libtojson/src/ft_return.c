/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:54:38 by deladia           #+#    #+#             */
/*   Updated: 2019/11/28 23:46:15 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

/*
** Функция для чистки всей структуры в случе ошибки
*/

void	ft_return(t_key_value **tree)
{
	int		i;

	i = 0;
	while ((*tree)->key[i])
	{
		free((*tree)->key[i]);
		*((*tree)->key + i++) = 0;
	}
	free((*tree)->key);
	while (--i >= 0)
	{
		if ((*tree)->value[i] == NULL)
			continue ;
		if ((*tree)->type[i] == Object)
			ft_return((t_key_value**)(*tree)->value);
		else
			free((*tree)->value[i]);
		*((*tree)->value + i) = 0;
	}
	free((*tree)->value);
	(*tree)->value = 0;
	free((*tree)->type);
	(*tree)->type = 0;
	free(*tree);
	*tree = 0;
}

/*
** добавить чистку маcсива когда она будет
*/
