/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:37:12 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/26 17:02:31 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	safe_get_char(t_map *map, int i, int j)
{
	if (i < 0 || i >= ft_strlen2(map->map))
		return (' ');
	if (j < 0 || j >= ft_strlen(map->map[i]))
		return (' ');
	return (map->map[i][j]);
}

static int	find_space(t_map *map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = safe_get_char(map, i - 1, j);
	down = safe_get_char(map, i + 1, j);
	left = safe_get_char(map, i, j - 1);
	right = safe_get_char(map, i, j + 1);
	if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
		return (1);
	return (0);
}

void	checkwalls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != ' ')
				if (find_space(map, i, j))
					errors("Error\nMap is not enclosed by walls\n", 1);
			j++;
		}
		i++;
	}
}
