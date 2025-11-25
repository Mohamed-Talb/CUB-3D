/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:33:15 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/14 10:51:20 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	checkelement(t_map *map, int i, int j, int *start)
{
	char	elem;

	elem = map->map[i][j];
	if (elem == 'S' || elem == 'N' || elem == 'E' || elem == 'W')
	{
		map->px = j + 0.5;
		map->py = i + 0.5;
		*start += 1;
	}
	else if (elem != '0' && elem != '1' && elem != 'S' && elem != 'E'
		&& elem != 'W' && elem != 'N' && elem != ' ')
		errors("Error\ninvalid element\n", 1);
}

void	mapvalidation(t_map *map)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	i = 0;
	checkwalls(map);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			checkelement(map, i, j, &start);
			j++;
		}
		i++;
	}
	if (start != 1)
		errors("Error\ninvalide elements\n", 1);
}
