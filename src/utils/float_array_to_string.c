/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_array_to_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:01:38 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 17:02:47 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*float_array_to_string(cl_float3 array)
{
	char	*tmp;
	char	*str;

	if (!(tmp = ft_strnew(5)))
		return (NULL);
	sprintf(tmp, "%3.2f", array.s[0]);
	tmp[4] = ' ';
	if (!(str = ft_strdup(tmp)))
		return (NULL);
	sprintf(tmp, "%3.2f", array.s[1]);
	tmp[4] = ' ';
	if (!(str = ft_strjoin_free(str, tmp, 1)))
		return (NULL);
	sprintf(tmp, "%3.2f", array.s[2]);
	tmp[4] = ' ';
	if (!(str = ft_strjoin_free(str, tmp, 3)))
		return (NULL);
	return (str);
}
