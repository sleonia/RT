/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:27:09 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 11:37:30 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

void		ft_array(void *tree_value)
{
	int		i;
	int**	d;

	i = 0;
	if ((t_array*)tree_value->type == Object)
	{
		while(i < tree_value->length)
		{
			ft_printf((t_key_value*)tree_value->value[i]);
			i++;
		}
	}
	else if ((t_array*)tree_value->type == String)
	{
		i = 0;
		printf("[");
		while(i < tree_value->length)
		{
			printf("%s  ", tree_value->value[i]);
			i++;
		}
		printf("]");
	}
	else if ((t_array*)tree_value->type == Dec)
	{
		d = (int**)(((t_key_value*)tree_value)->value);
		i = 0;
		printf("[");
		while(i < ((t_key_value*)tree_value)->length)
		{
			printf("%s  ", d[i]);
			i++;
		}
		printf("]");
	}
}

void		ft_print(t_key_value *tree)
{
	int 	i;

	i = 0;
	while (tree->key[i] != NULL)
	{
		if (tree->type[i] == Array)
		{
			 (t_array*)(tree->value)->type == 
			//Печатать массив
		}
		else if (tree->type[i] == String)
		{
			printf("value: %s\nkey: %s\n", tree->value[i], tree->key[i]);
		}
		else if (tree->type[i] == Dec)
		{
			printf("value: %d\nkey: %s\n", ((int*)tree->value[i])[0], tree->key[i]);
		}
		else if (tree->type[i] == Doub)
		{
			printf("value: %lf\nkey: %s\n", ((double*)tree->value[i])[0], tree->key[i]);
		}
		else if (tree->type[i] == None)
		{
			printf("value: NULL\nkey: %s\n", tree->key[i]);
		}
		else if (tree->type[i] == Object)
			ft_print((t_key_value*)tree->value[i]);
		i++;
	}
}
