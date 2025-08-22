#include "../cub3d.h"

static int	countlines(char *file)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	// if (fd == -1)
        // error
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

// static char *trim_spaces(char *str)
// {
// 	int len = strlen(str);
// 	char *result = ft_malloc(len + 1);
// 	int j = 0;
// 	int i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_iswhitespace(str[i]))
//         {
// 			result[j] = str[i];
//             j++;
//         }
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return result;
// }

static int is_empty_line(const char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
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
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		clear = ft_strtrim(line, "\n");
		ft_free(line);
		cub->file[count++] = clear;
		
	}
	cub->file[count] = NULL;
	close(fd);
}
