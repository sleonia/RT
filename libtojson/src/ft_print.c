/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:27:09 by deladia           #+#    #+#             */
/*   Updated: 2019/12/01 02:44:05 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

/*
** функция для печати всего дерева
*/

void		ft_print(t_key_value *tree)
{
	int		i;

	i = 0;
	while (tree->key[i] != NULL)
	{
		if (tree->type[i] == String)
		{
			printf("key: %s\nvalue: %s\n", tree->key[i], tree->value[i]);
		}
		else if (tree->type[i] == Dec)
		{
			printf("key: %s\nvalue: %d\n", tree->key[i], ((int*)tree->value[i])[0]);
		}
		else if (tree->type[i] == Doub)
		{
			printf("key: %s\nvalue: %lf\n", tree->key[i], ((double*)tree->value[i])[0]);
		}
		else if (tree->type[i] == None)
		{
			printf("key: %s\nvalue: NULL\n", tree->key[i]);
		}
		else if (tree->type[i] == Object)
		{
			printf("key: %s\nvalue:{\n", tree->key[i]);
			ft_print((t_key_value*)tree->value[i]);
			printf("}\n");
		}
		i++;
	}
}
