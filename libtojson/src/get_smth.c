/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:32:42 by deladia           #+#    #+#             */
/*   Updated: 2020/01/18 19:49:13 by thorker          ###   ########.fr       */
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

int		get(t_key_value *tree, char *name, void **object)
{
	int		error;
	void	*container;

	error = 0;
	if (object == NULL)
		return (WRONG_CONTAINER);
	container = ft_find(tree, name, 0, &error);
	if (error == 0)
		*object = container;
	return (error);
}
