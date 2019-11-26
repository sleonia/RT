/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_key_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:14:59 by thorker           #+#    #+#             */
/*   Updated: 2019/11/26 19:43:49 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

/*
** Замена старых массивов на новые
*/

static void	ft_free(t_key_value *for_re,
		char **new_key_array,
		void **new_value_array,
		t_type *new_type_array)
{
	free(for_re->key);
	free(for_re->value);
	if (for_re->type != 0)
		free(for_re->type);
	for_re->key = new_key_array;
	for_re->value = new_value_array;
	for_re->type = new_type_array;
}

/*
** выделение памяти, проверка маллоко, копирование данных в новые массивы
*/

static int	realloc_struct(t_key_value *for_re, size_t i)
{
	char	**new_key_array;
	void	**new_value_array;
	t_type	*new_type_array;

	if ((new_key_array = (char**)malloc(sizeof(char*) * (i + 2))) == 0 |
			(new_value_array = (void**)malloc(sizeof(void*) * (i + 1))) == 0 |
			(new_type_array = (t_type*)malloc(sizeof(t_type) * (i + 1))) == 0)
	{
		if (new_key_array != 0)
			free(new_key_array);
		if (new_value_array != 0)
			free(new_value_array);
		if (new_type_array != 0)
			free(new_type_array);
		return (0);
	}
	while (i-- != 0)
	{
		*(new_key_array + i) = *(for_re->key + i);
		*(new_value_array + i) = *(for_re->value + i);
		*(new_type_array + i) = *(for_re->type + i);
	}
	ft_free(for_re, new_key_array, new_value_array, new_type_array);
	return (1);
}

/*
** функция в которой выделяется новая память для расширенного массива
*/

int			realloc_key_value(t_key_value *for_re,
		char *new_key,
		void *new_value,
		t_type new_type)
{
	size_t	i;

	i = 0;
	while (*(for_re->key + i) != 0)
		i++;
	if (realloc_struct(for_re, i) == 0)
		return (0);
	*(for_re->key + i) = new_key;
	*(for_re->key + i + 1) = 0;
	*(for_re->value + i) = new_value;
	*(for_re->type + i) = new_type;
	return (1);
}
