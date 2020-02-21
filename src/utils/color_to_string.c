/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_to_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:42:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/21 04:59:10 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*color_to_string(cl_float3 array)
{
	char	*tmp;
	char	*str;

	if (!(tmp = ft_strnew(5)))
		return (NULL);
	sprintf(tmp, "%3d", (int)(array.s[0] * 255));
	// printf("%lu\n", strlen(tmp));
	tmp[3] = ' ';
	if (!(str = ft_strdup(tmp)))
		return (NULL);
	sprintf(tmp, "%3d", (int)(array.s[1] * 255));
	tmp[3] = ' ';
	if (!(str = ft_strjoin_free(str, tmp, 1)))
		return (NULL);
	sprintf(tmp, "%3d", (int)(array.s[2] * 255));
	tmp[3] = ' ';
	if (!(str = ft_strjoin_free(str, tmp, 3)))
		return (NULL);
	return (str);
}
