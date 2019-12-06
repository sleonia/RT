#include "rtv1.h"

int		read_kernel(t_cl *cl)
{
	char	*line;
	char	*tmp;
	int		fd;

	if (!(cl->program_source = (char *)ft_memalloc(sizeof(char))))
		ft_error("Memory not allocated");
	if ((fd = open("./kernel.cl", O_RDONLY)) < 0)
		ft_error("Can't open file");
	while ((get_next_line(fd, &line)) > 0)
	{
		tmp = cl->program_source;
		cl->program_source = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	cl->program_size = ft_strlen(cl->program_source);
	return (0);
}
