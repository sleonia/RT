/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_string_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:49:34 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 04:49:36 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_destroy_string_arr(char **arr)
{
	int			i;

	i = -1;
	if (arr && arr[0])
	{
		while (arr[++i])
			;
		while (--i >= 0)
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
	else if (arr)
	{
		free(arr);
	}
}
