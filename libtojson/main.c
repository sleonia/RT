/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:54:41 by deladia           #+#    #+#             */
/*   Updated: 2020/01/20 19:26:23 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "to_json.h"


void	free_token(t_token **token)
{
	t_token		*tmp;

	tmp = *token;
	while(tmp)
	{
		*token = tmp;
		if (tmp->next)
			tmp = tmp->next;
		free((*token)->value);
		free(token);
	}
}


int		main(void)
{
	t_key_value	*tmp;
	t_key_value *node;
	double		b;
	int error;
//	tmp = parse_json("../../../param.json");
	tmp = parse_json("test.json");
	error = get_node(tmp, "light", &node);
	error = get_double(node, "intensity", &b);
	printf("вот тот double %lf\n",b);

	//ft_print(tmp);
	/*
	char *line = 0;
	size_t k = read(0, line, 3);
	(void)k;
	*/
	ft_return(&tmp);
	return (0);
}
