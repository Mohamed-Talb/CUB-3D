/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:32:31 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/26 16:57:40 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_trimed(int fd)
{
	char	*line;
	char	*result;

	line = get_next_line(fd);
	result = ft_strtrim(line, "\n");
	ft_free(line);
	return (result);
}

char	*sidescheck(char *line)
{
	char	**path;
	char	*result;

	if (!in_set(WHITESPACES, *line))
		errors("Error\nInvalide components\n", 1);
	path = ft_splitpro(line, ft_iswhitespace);
	if (ft_strlen2(path) != 1)
		errors("Error\nInvalide components\n", 1);
	result = ft_strdup(path[0]);
	ft_freedouble(path);
	return (result);
}

void	initeyes(t_game *cub)
{
	char	pl;
	int		px;
	int		py;

	px = cub->map->px;
	py = cub->map->py;
	pl = cub->map->map[py][px];
	if (pl == 'N')
		cub->player->viewangle = -90;
	else if (pl == 'S')
		cub->player->viewangle = 90;
	else if (pl == 'E')
		cub->player->viewangle = 0;
	else if (pl == 'W')
		cub->player->viewangle = 180;
	cub->map->map[py][px] = '0';
}
