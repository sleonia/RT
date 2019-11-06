/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:54:38 by deladia           #+#    #+#             */
/*   Updated: 2019/11/06 23:56:38 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"
//добавить проверку на null v value
t_token 	*ft_return(t_token *token, t_key_value **tree)
{
	int 	i;
	int 	len;

	i = 0;
	while((*tree)->key[i])
		free((*tree)->key[i++]);
	free((*tree)->key);
	len = i;
	i = 0;
	while (i < len)
		free((*tree)->value[i++]);
	free((*tree)->value);
	free((*tree)->type);
	return (token);
}
