/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opencl_files_json.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:19:02 by sleonia           #+#    #+#             */
/*   Updated: 2020/01/28 20:49:23 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char				**parse_opencl_files_json(t_key_value *json)
{
	int				i;
	char			**files;
	char			*arg;
	char			*file_name;
	t_key_value		*opencl;

	i = -1;
	if (!(files = (char **)ft_memalloc(sizeof(char *) * 4)))
		ft_error("Malloc");		
	if (get_node(json, "opencl", &opencl) != 0)
		ft_error("get_node: opencl");
	file_name = ft_strdup("file_0");
	while (get_str(opencl, file_name, &arg) == 0)
	{
		if (!arg)
			ft_error("Error arg");
		files[++i] = arg;
		if (!(file_name = get_next_name(file_name)))
			ft_error("Error songs_name");
	}
	ft_strdel(&file_name);
	return (files);
}
