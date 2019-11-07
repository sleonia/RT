/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:54:41 by deladia           #+#    #+#             */
/*   Updated: 2019/11/07 23:04:52 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tojson.h"

int		main(void)
{
	t_key_value		*tmp;
	t_token			*token;

	token = ft_open("../param.json");
	if (ft_strcmp(token->value, "{") == 0)
			tmp = check_object(token);
	else
		ft_error("ERROR");
	return (0);
}
