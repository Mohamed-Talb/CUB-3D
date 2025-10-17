#include "../cub3d.h"

static int	countlines(char *file)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		errors(strerror(errno), 1);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void filecontent(t_game *cub, char *file)
{
	int		count;
	int		fd;
	char	*line;
	char	*clear;

	count = countlines(file);
	cub->file = ft_malloc(sizeof(char *) * (count + 1));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		errors(strerror(errno), 1);
	count = 0;
	line = get_next_line(fd);
	while(line)
	{
		clear = ft_strtrim(line, "\n");
		cub->file[count++] = clear;
		ft_free(line);
		line = get_next_line(fd);
	}
	cub->file[count] = NULL;
	close(fd);
}
