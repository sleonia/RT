/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:06:17 by deladia           #+#    #+#             */
/*   Updated: 2019/12/11 16:12:44 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		read_kernel(t_cl *cl)
{
	char		line[32];
	char		*tmp;
	int			fd;
	ssize_t		ret;

	if (!(cl->program_source = (char *)ft_memalloc(sizeof(char))))
		ft_error("Memory not allocated");
	if ((fd = open("./src/kernel.cl", O_RDONLY)) < 0)
		ft_error("Can't open file");
	while ((ret = read(fd, line, 32)) > 0)
	{
		tmp = cl->program_source;
		line[ret] = '\0';
		cl->program_source = ft_strjoin(tmp, line);
		free(tmp);
	}
	cl->program_size = ft_strlen(cl->program_source);
	return (0);
}
