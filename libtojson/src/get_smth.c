/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:32:42 by deladia           #+#    #+#             */
/*   Updated: 2020/01/20 23:01:33 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"

void	*ft_find(t_key_value *tree, char *name, t_type type, int *error)
{
	int	i;

	i = 0;
	if (tree == 0 || tree->key == 0 || tree->value == 0 || tree->type == 0 ||
			name == 0)
	{
		*error = BROKEN_NODE;
		return (0);
	}
	while (tree->key[i])
	{
		if (ft_strcmp(tree->key[i], name) == 0)
		{
			if (tree->type[i] == type || type == 0)
				return (tree->value[i]);
			else
			{
				*error = WRONG_TYPE;
				return (0);
			}
		}
		i++;
	}
	*error = (NOT_FOUND);
	return (0);
}
int		get_int(t_key_value *tree, char *name, int *number)
{
	int		error;
	void	*container;

	error = 0;
	if (number == NULL)
		return (WRONG_CONTAINER);
	container = ft_find(tree, name, Dec, &error);
	if (error == 0)
		*number = *((int*)container);
	return (error);
}

int		get_node(t_key_value *tree, char *name, t_key_value **object)
{
	int		error;
	void	*container;

	error = 0;
	if (object == NULL)
		return (WRONG_CONTAINER);
	container = ft_find(tree, name, Object, &error);
	if (error == 0)
		*object = (t_key_value*)container;
	return (error);
}

int		get_double(t_key_value *tree, char *name, double *number)
{
	int		error;
	void	*container;

	error = 0;
	if (number == NULL)
		return (WRONG_CONTAINER);
	container = ft_find(tree, name, Doub, &error);
	if (error == 0)
		*number = *((double*)container);
	return (error);
}

int		get_str(t_key_value *tree, char *name, char **str)
{
	int		error;
	void	*container;

	error = 0;
	if (str == NULL)
		return (WRONG_CONTAINER);
	container = ft_find(tree, name, String, &error);
	if (error == 0)
		*str = (char*)container;
	return (error);
}

int		get_array(t_key_value *tree, char *name, t_array **array)
{
	int		error;
	void	*container;

	error = 0;
	if (array == NULL)
		return (WRONG_CONTAINER);
	container = ft_find(tree, name, Array, &error);
	if (error == 0)
		*array = (t_array*)container;
	return (error);
}

void	*find_in_array(t_array *array, size_t item, t_type type, int *error)
{
	if (array == 0)
	{
		*error = BROKEN_ARRAY;
		return (0);
	}
	if (item >= array->length)
	{
		*error = OUT_OF_RANGE;
		return (0);
	}
	if (type != 0 && array->type[item] != type)
	{
		*error = WRONG_TYPE;
		return (0);
	}
	return (array->value[item]);
}

int		getf_int_array(t_array *array, size_t item, int *number)
{
	void	*container;
	int		error;

	if (number == 0)
		return(WRONG_CONTAINER);
	error = 0;
	container = find_in_array(array, item, Dec, &error);
	if (error == 0)
		*number = *((int*)container);
	return (error);
}

int		getf_double_array(t_array *array, size_t item, int *number)
{
	void	*container;
	int		error;

	if (number == 0)
		return(WRONG_CONTAINER);
	error = 0;
	container = find_in_array(array, item, Doub, &error);
	if (error == 0)
		*number = *((double*)container);
	return (error);
}

int		getf_object_array(t_array *array, size_t item, t_key_value **object)
{
	void	*container;
	int		error;

	if (object == 0)
		return(WRONG_CONTAINER);
	error = 0;
	container = find_in_array(array, item, Object, &error);
	if (error == 0)
		*object = (t_key_value*)container;
	return (error);
}

int		getf_array_array(t_array *array, size_t item, t_array **new_array)
{
	void	*container;
	int		error;

	if (new_array == 0)
		return(WRONG_CONTAINER);
	error = 0;
	container = find_in_array(array, item, Array, &error);
	if (error == 0)
		*new_array = (t_array*)container;
	return (error);
}

int		getf_str_array(t_array *array, size_t item, char **str)
{
	void	*container;
	int		error;

	if (str == 0)
		return(WRONG_CONTAINER);
	error = 0;
	container = find_in_array(array, item, String, &error);
	if (error == 0)
		ft_strcpy(*str, container);
	return (error);
}
