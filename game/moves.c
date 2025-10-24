/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:18:28 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 11:02:33 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	isc(t_map *map, t_move move)
{
	return (map->map[(int)map->py][(int)move.safe_px] == '0'
		&& map->map[(int)move.safe_py][(int)map->px] == '0'
		&& map->map[(int)move.safe_py][(int)move.safe_px] == '1');
}

void	godirection(t_game *cub, double step, int direction, t_map *map)
{
	t_move		move;
	int			range;
	t_player	*player;

	player = cub->player;
	move.edge_decision = 0;
	move.added_x = (step * direction) * cos(player->viewangle * (M_PI / 180));
	move.added_y = (step * direction) * sin(player->viewangle * (M_PI / 180));
	move.safe_px = map->px + player->collisionmargin;
	move.safe_py = map->py + player->collisionmargin;
	if (move.added_x < 0)
		move.safe_px = map->px - player->collisionmargin;
	if (move.added_y < 0)
		move.safe_py = map->py - player->collisionmargin;
	if (isc(map, move))
	{
		range = fabs(cos(player->viewangle * (M_PI / 180.0))) > sqrt(2) / 2;
		move.edge_decision = 1 + range;
	}
	collision(map, move);
}

static void	key_hook_helper(t_game *cub, double step, double turn, double angle)
{
	double	tmp;

	if (cub->keys.up == true)
		godirection(cub, step, 1, cub->map);
	if (cub->keys.down == true)
		godirection(cub, step, -1, cub->map);
	if (cub->keys.left == true)
	{
		tmp = cub->player->viewangle;
		cub->player->viewangle = angle;
		godirection(cub, step, -1, cub->map);
		cub->player->viewangle = tmp;
	}
	if (cub->keys.right == true)
	{
		tmp = cub->player->viewangle;
		cub->player->viewangle = angle;
		godirection(cub, step, 1, cub->map);
		cub->player->viewangle = tmp;
	}
	if (cub->keys.rot_left == true)
		cub->player->viewangle -= turn;
	if (cub->keys.rot_right == true)
		cub->player->viewangle += turn;
}

void	key_hook(t_game *cub, double fdiff)
{
	double	step;
	double	turn;
	double	strafe_angle;

	step = fdiff * cub->player->traverseperiod;
	turn = fdiff * 360 / cub->player->turnperiod;
	strafe_angle = cub->player->viewangle + 90;
	key_hook_helper(cub, step, turn, strafe_angle);
}
