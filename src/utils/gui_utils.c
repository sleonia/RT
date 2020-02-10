/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:43:41 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 15:48:35 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*pop_back(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!str[i + 1])
		{
			str[i] = '\0';
			return (str);
		}
	}
	return (str);
}

int		get_width(t_textbox *textbox)
{
	return (textbox->m_width);
}

int		get_height(t_textbox *textbox)
{
	return (textbox->m_height);
}

