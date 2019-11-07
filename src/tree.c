/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:55:14 by delalia           #+#    #+#             */
/*   Updated: 2019/11/08 00:10:36 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"
#include "rtv1.h"
//проблема с пустой строкой
//проблема с пустым массивом
int				*ft_str_is_digit(char* str)
{
	int i;

	i = 0;
	if (str == 0)
		return (0);
	while (*(str + i) != 0)
	{
		if (ft_isdigit(*(str + i)) == 0)
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int				*ft_str_is_double(char* str)
{
	int	i;
	int	flag;

	if (str == 0)
		return (0);
	i = 0;
	flag = 0;
	while (*(str + i) != 0)
	{
		if (ft_isdigit(*(str + i)) == 0)
		{
			if (*(str + i) == '.' && flag != 1)
				flag = 1;
			else
				return (0);
		}
		i++;
	}
	if (flag == 0 || i == 0)
		return (0);
	return (1);
}

void			*check_string(t_token **token, t_type *type)
{
	char	*new_str;

	if ((*token)->next == 0)
		return (*token);
	*token = (*token)->next;
	new_str = ft_strdup((*token)->value);
	if ((*token)->next == 0)
	{
		free(new_str);
		return (*token);
	}
	*token = (*token)->next;
	if (ft_strcmp((*token)->value, "\"") != 0)
	{
		free(new_str);
		return (*token);
	}
	*token = (*token)->next;
	*type = String;
	return (new_str);
}
/*
void			*check_array(t_token **token, t_type *type)
{
	t_array		new_array;
	size_t		i;
	size_t		k;
	t_token		*my_token;
	

	my_token = (*token)->next;
	i = 0;
	k = 0;
	while (my_token != 0)
	{
		if (ft_strcmp(my_token->value, ",") == 0)
		{
			if (k % 2 == 0)
				return (*token);
			else
				i++;
		}
		if (ft_strcmp(my_token->value, "]") == 0)
		{
			if (k % 2 == 1)
			{
				i++;
				break ;
			}
			else
				return (*token);
		}
		my_token = my_token->next;
		k++
	}
	if (my_token == 0)
		return (*token);
	if (i == 0)
		return (*token);


}
*/
int				add_name(t_key_value *for_re, t_token **token)
{
	char	**new;
	size_t	i;
	size_t	k;
	t_type	type;
	void	*new_value;
	void	**new_array_value;
	void	*new_array_type;

	i = 0;
	type = 0;
	while (*(for_re->key + i) != 0)
		i++;
	new = (char**)malloc(sizeof(char*) * (i + 2));
	k = 0;
	while (k <= i)
	{
		*(new + k) = ft_strdup(*(for_re->key + k));
		//подумать может можно обойтись и без strdel
		ft_strdel(for_re->key + k);
		k++;
	}
	*(new + k) = ft_strdup((*token)->value);
	*(new + k + 1) = 0;
	*token = (*token)->next;
	if (*token == 0 || ft_strcmp((*token)->value, "\"") != 0 ||
			(*token = (*token->next)) == 0 || ft_strcmp((*token)->value, ":") != 0
			|| (*token = (*token->next)) == 0)
	{
		k = 0;
		while (k < i + 2)
		{
			ft_strdel(new + k);
			k++;
		}
		free(new);
		return (-1);
	}
	/*
	if (ft_strcmp((*token)->value, "[") == 0)
	{
		if ((new_value = check_array(token, &type)) == *token)
		{
			k = 0;
			while (k < i + 2)
			{
				ft_strdel(new + k);
				k++;
			}
			free(new);
			return (-1);
		}
	}*/
	if (ft_strcmp((*token)->value, "{") == 0)	
	{
		if ((new_value = check_object(token, &type)) == *token)
		{
			
			k = 0;
			while (k < i + 2)
			{
				ft_strdel(new + k);
				k++;
			}
			free(new);
			return (-1);
		}
		type = Object;
	}
	if (ft_strcmp((*token)->value, "\"") == 0)
	{
		
		if ((new_value = check_string(token, &type)) == *token)
		{
			k = 0;
			while (k < i + 2)
			{
				ft_strdel(new + k);
				k++;
			}
			free(new);
			return (-1);
		}
		type = String;
	}
	if (ft_str_is_digit((*token)->value) == 1)
	{
		new_value = (int*)malloc(sizeof(int));
		*new_value = ft_atoi(*(token)->value);
		type = Dec;
		*token = (*token)->next;
	}
	if (ft_str_is_double((*token)->value) == 1)
	{
		new_value = (int*)malloc(sizeof(int));
		*new_value = ft_atof(*(token)->value);
		type = Doub;
		*token = (*token)->next;
	}
	if (ft_strcmp((*token)->value, "null") == 0)
	{
		new_value = 0;
		type = None;
		*token = (*token)->next;
	}
	if (type != 0)
	{
		new_array_value = (void**)malloc(sizeof(void*) * (i + 1));
		new_array_type = (t_type*)malloc(sizeof(t_type) * (i + 1));
		k = 0;
		while (k < i)
		{
			*(new_array_value + k) = *(for_re->value + k);
			*(new_array_type + k) = *(for_re->type + k);
			k++;
		}
		*(new_array_value + k) = new_value;
		*(new_array_type + k) = type;
		free(for_re->value);
		for_re->value = new_array_value;
		free(for_re->type);
		for_re->type = new_type_array;
		free(for_re->key);
		for_re->key = new;
	}
	else
		return (-1);
	return (0);
}

t_key_value		*check_object(t_token **token)
{
	t_key_value		*for_re;
	if ((*token)->next != 0 && ft_strcmp((*token)->next->value, "}") != 0)
		return (0);
	else
	{
		for_re = (t_key_value*)malloc(sizeof(t_key_value));
		for_re->key = (char**)malloc(sizeof(char*));
		*(for_re->key) = 0;
		for_re->value = (void**)malloc(sizeof(void*));
		*(for_re->value) = 0;
		for_re->type = (char**)malloc(sizeof(char*));
		*(for_re->type) = 0;
	}
	*token = (*token)->next;
	while (*token != 0)
	{
		if (ft_strcmp((*token)->value, "\"") == 0)
		{
			*token = (*token)->next;
			//проверить на null и занести в token
			if (add_name(for_re, token) != 0)
			{
				fr_return(*token, for_re);
				return (*token);
			}
		}
		else if (ft_strcmp((*token)->value, "}") == 0)
			return (for_re);
		else if (ft_strcmp((*token)->value, ",") == 0)
			*token = (*token)->next;
		else
			return (*token);
	}
	return (*token);
}

//проверить "{" в самом начале (до этой функции)
//считается ли {} null или нет
//что делать если   token == 0
