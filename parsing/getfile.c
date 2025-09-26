#include "../cub3d.h"

static int	countlines(char *file)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		//error
		exit(1);
	}
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

void filecontent(t_game *cub, char *file)
{
	int     count;
	int     fd;
	char    *line;
	char 	*clear;

	count = countlines(file);
	cub->file = ft_malloc(sizeof(char *) * (count + 1));
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
        // errors
		return;
	}
	count = 0;
	while ((line = get_next_line(fd)))
	{
		clear = ft_strtrim(line, "\n");
		ft_free(line);
		cub->file[count++] = clear;	
	}
	cub->file[count] = NULL;
	close(fd);
}
