/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:14:23 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 19:32:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_len_nbr(int nbr)
{
	int		len;

	len = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		++len;
	}
	return (len);
}

static int	ft_find_symb(const char symb, const char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == symb)
			return (i);
	}
	return (0);
}

char		*get_next_name(char *name)
{
	int		value;
	char	*str2;
	int		border_cymb;
	char	*limited_name;
	char	*new_name;

	if (!(border_cymb = ft_find_symb('_', name)))
		ft_error("Error");
	value = ft_atoi((char *)name + border_cymb + 1) + 1;
	if (!(limited_name = ft_strnew(ft_strlen(name) + 1000000)))
		return (NULL);
	limited_name = ft_strncpy(limited_name, name, border_cymb + 1);
	str2 = ft_itoa(value);
	new_name = ft_strjoin(limited_name, str2);
	ft_strdel(&str2);
	ft_strdel(&name);
	ft_strdel(&limited_name);
	return (new_name);
}
