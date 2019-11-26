/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_key_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:14:59 by thorker           #+#    #+#             */
/*   Updated: 2019/11/26 17:42:44 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"
/*
int			realloc_struct(t_key_value	*for_re, size_t i)
{
	char    **new_key_array;
	void    **new_value_array;
	t_type  *new_type_array;
	if ((new_key_array = (char**)malloc(sizeof(char*) * (i + 2))) == 0) &&
		
}
*/
/*
 * функция в которой выделяется новая память для расширенного массива
 */
int		realloc_key_value(t_key_value *for_re, char* new_key, void *new_value, t_type new_type)
{
	size_t  i;
	char    **new_key_array;
	void    **new_value_array;
	t_type  *new_type_array;
	size_t  k;

	i = 0;
	while (*(for_re->key + i) != 0)
		i++;
	if ((new_key_array = (char**)malloc(sizeof(char*) * (i + 2))) == 0)
		return (0);
	if ((new_value_array = (void**)malloc(sizeof(void*) * (i + 1))) == 0)
	{
		free(new_key_array);
		return (0);
	}
	if ((new_type_array = (t_type*)malloc(sizeof(t_type) * (i + 1))) == 0)
	{
		free(new_key_array);
		free(new_value_array);
		return (0);
	}
	k = 0;
	while (k < i)
	{
		*(new_key_array + k) = *(for_re->key + k);
		*(new_value_array + k) = *(for_re->value + k);
		*(new_type_array + k) = *(for_re->type + k);
		k++;
	}
	*(new_key_array + k) = new_key;
	*(new_key_array + k + 1) = 0;
	*(new_value_array + k) = new_value;
	*(new_type_array + k) = new_type;
	free(for_re->key);
	free(for_re->value);
	if (for_re->type != 0)
		free(for_re->type);
	for_re->key = new_key_array;
	for_re->value = new_value_array;
	for_re->type = new_type_array;
	return (1);
}
