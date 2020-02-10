/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:26:17 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 16:27:30 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_strjoin_free(char *s1, char *s2, int num)
{
	size_t	ct;
	size_t	ct2;
	char	*nw;

	ct = -1;
	ct2 = ct;
	if (NULL == s2 || NULL == s1)
		return (NULL);
	if (!(nw = ft_strjoin(s1, s2)))
		return (NULL);
	if (num == 1)
		ft_strdel(&s1);
	else if (num == 2)
		ft_strdel(&s2);
	else if (num == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (nw);
}
