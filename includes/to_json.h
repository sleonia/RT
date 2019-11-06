/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_json.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:50:08 by thorker           #+#    #+#             */
/*   Updated: 2019/11/06 21:51:44 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_JSON_H
# define TO_JSON_H

#include "libft.h"

typedef struct		s_key_value
{
	char	**key;
	void	**value;
	char	**type;
}					t_key_value;
#endif
