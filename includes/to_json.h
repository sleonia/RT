/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_json.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:50:08 by thorker           #+#    #+#             */
/*   Updated: 2019/11/07 23:54:26 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_JSON_H
# define TO_JSON_H

#include "libft.h"

typedef enum			e_type
{
	Object = 1,
	Array,
	String,
	Dec,
	Doub,
	None
}						t_type;

typedef struct			s_array
{
	void				**value;
	size_t				length;
	t_type				type;
}						t_array;

typedef struct			s_key_value
{
	char				**key;
	void				**value;
	t_type				*type;
}						t_key_value;

typedef struct			s_token
{
	char				*value;
	t_type				type;
	struct s_token		*next;
}						t_token;

t_token					*ft_return(t_token *token, t_key_value **tree);
void					ft_print(t_key_value *tree);

#endif
