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
	char			**key;
	void			**value;
	char			**type;
}					t_key_value;

typedef enum			e_type
{
	Object = 1,
	Subobject,
	Light_properties,
	Camera_properties,
	Figure_properties,
	Light_type,
	Separator,
	Id_light,
	Id_sphere,
	Id_cone,
	Id_cylinder,
	Id_plane,
	Hex,
	Dec,
	Double_presition,
	None
}						t_type;

typedef struct			s_token
{
	char				*value;
	t_type				type;
	struct s_token		*next;
}						t_token;

#endif
