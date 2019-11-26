/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:54:38 by deladia           #+#    #+#             */
/*   Updated: 2019/11/26 15:21:56 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

void 	ft_return(t_key_value **tree)
{
	int 	i;
	int 	len;

	i = 0;
	while((*tree)->key[i])
	{
		free((*tree)->key[i]);
		*((*tree)->key + i++) = 0;
	}
	free((*tree)->key);
	len = i;
	i = 0;
	while (i < len)
	{
		if ((*tree)->value == NULL)
			continue ;
		free((*tree)->value[i]);
		*((*tree)->value + i++) = 0;
	}
	free((*tree)->value);
	(*tree)->value = 0;
	free((*tree)->type);
	(*tree)->type = 0;
	free(*tree);
	*tree = 0;
}
// а что если в валуе находится структура

