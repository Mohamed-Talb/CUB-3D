/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:41:41 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 09:41:42 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	adjust_colision(double pos, double added_value)
{
	if (added_value > 0)
		return (ceil(pos) - 0.299);
	else
		return (floor(pos) + 0.299);
}

int	get_safe_tile(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || y >= ft_strlen2(map->map)
		|| x >= ft_strlen(map->map[(int) y]))
		return (0);
	return (map->map[(int) y][(int) x]);
}

void	collision(t_map *map, t_move move)
{
	if (move.edge_decision != 1)
	{
		if (get_safe_tile(map, move.safe_px, map->py) == '0'
			&& get_safe_tile(map, map->px + move.added_x, map->py) == '0')
			map->px += move.added_x;
		else
			map->px = adjust_colision(map->px, move.added_x);
	}
	if (move.edge_decision != 2)
	{
		if (get_safe_tile(map, map->px, move.safe_py) == '0'
			&& get_safe_tile(map, map->px, map->py + move.added_y) == '0')
			map->py += move.added_y;
		else
			map->py = adjust_colision(map->py, move.added_y);
	}
}
