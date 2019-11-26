/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:32:42 by deladia           #+#    #+#             */
/*   Updated: 2019/11/26 16:59:26 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

int 	get_int(t_key_value *tree, char *name, int *number)
{
	int 	i;

	i = 0;
	if (number == NULL)
		return (WRONG_CONTAINER);
	while(tree->key[i])
	{
		if (ft_strcmp(tree->key[i], name) == 0)
		{
			if (tree->type[i] == Dec)
			{
				*number = *(int*)tree->value[i];
				return (0);
			}
			else
				return(WRONG_TYPE);
		}
		i++;
	}
	return (NOT_FOUND);
}
