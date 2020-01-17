/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_json.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:50:08 by thorker           #+#    #+#             */
/*   Updated: 2020/01/17 19:17:24 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_JSON_H
# define TO_JSON_H
# define WRONG_TYPE -1
# define NOT_FOUND -2
# define WRONG_CONTAINER -3
# include "libft.h"

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
	t_type				*type;
	size_t				length;
}

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
void					*check_value(t_token **token, t_type *type);
int						ft_token_isstr(t_token **token);
char					*make_string(char *str);
int						realloc_key_value(t_key_value *for_re, char *new_key,
		void *new_value, t_type new_type);
int						get_int(t_key_value *node, char	*name, int *container);
t_key_value				*parse_json(char *file_name);
t_token					*ft_open(char *file);
void					*make_object(t_token **token);
void					ft_return(t_key_value **tree);
void					ft_print(t_key_value *tree);
t_token					*create_token(char *word, t_token *token);
void					ft_error(char *str);
void					*make_digit(t_token **token);
int						ft_str_isdigit(char *str);
int						ft_str_isdouble(char *str);
void					*make_double(t_token **token);
#endif
