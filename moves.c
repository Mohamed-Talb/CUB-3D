#include "cub3d.h"

static int isc(t_map *map, t_move move)
{
    return 
    (
        map->map[(int)map->py][(int)move.safe_px] == '0' &&
        map->map[(int)move.safe_py][(int)map->px] == '0' &&
        map->map[(int)move.safe_py][(int)move.safe_px] == '1'
    );
}

void godirection(t_game *cub, double step, int direction, t_map *map)
{
    t_move move;
    int range;

    move.edge_decision = 0;
    move.added_x = (step * direction) * cos(DEG_TO_RAD(cub->player->viewangle));
    move.added_y = (step * direction) * sin(DEG_TO_RAD(cub->player->viewangle));

    move.safe_px = map->px + cub->player->collisionmargin;
    move.safe_py = map->py + cub->player->collisionmargin;

    if (move.added_x < 0)
        move.safe_px = map->px - cub->player->collisionmargin;
    if (move.added_y < 0)
        move.safe_py = map->py - cub->player->collisionmargin;
    if (isc(map, move))
    {
        range = fabs(cos(cub->player->viewangle * (M_PI / 180.0))) > sqrt(2) / 2;
        move.edge_decision = 1 + range;
    }
    collision(map, move);
}


void	key_hook(t_game *cub, double fdiff)
{
    double step;
    double turn;

    step = fdiff * cub->player->traverseperiod;
    turn = fdiff * 360 / cub->player->turnperiod;
	if (cub->keys.up == true)
        godirection(cub, step, 1, cub->map);
	if (cub->keys.down == true)
        godirection(cub, step, -1, cub->map);
	if (cub->keys.left == true)
        cub->player->viewangle -= turn;
	if (cub->keys.right == true)
        cub->player->viewangle += turn;
}