/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <deladia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:06:17 by deladia           #+#    #+#             */
/*   Updated: 2020/01/25 02:52:18 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_count_files_cl(char **file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		i++;
	}
	return (i);
}

int		ft_read_kernel(char *files_cl, size_t *program_size, char **program_source)
{
	int			fd;
	ssize_t		ret;
	char		line[32];
	char		*tmp;

	if ((fd = open(files_cl, O_RDONLY)) < 0)
		ft_error("Can't open file");
	if (!(*program_source = (char *)ft_memalloc(sizeof(char))))
		ft_error("Memory not allocated");
	while ((ret = read(fd, line, 32)) > 0)
	{
		tmp = *program_source;
		line[ret] = '\0';
		*program_source = ft_strjoin(tmp, line);
		free(tmp);
	}
	*program_size = ft_strlen(*program_source);
	return (0);
}

void	contain_program_source(char **program_source, size_t *program_size, char **files_cl, int cnt_files)
{
	int		i;
	int		ret;

	i = 0;
	while (i < cnt_files)
	{
		ret = ft_read_kernel(files_cl[i], &program_size[i], &program_source[i]);
		i++;
	}
}

int		read_kernel(t_cl *cl, char **files_cl)
{
	cl->count_files = get_count_files_cl(files_cl);
	if (!(cl->program_source = (char **)ft_memalloc(sizeof(char *) * cl->count_files)))
		ft_error("Memory not allocated");
	if (!(cl->program_size = (size_t *)ft_memalloc(sizeof(size_t) * cl->count_files)))
		ft_error("Memory not allocated");
	contain_program_source(cl->program_source, cl->program_size, files_cl, cl->count_files);
	return (0);
}
