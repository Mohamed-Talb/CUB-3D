#include "cub3d.h"
double adjust_colision(double pos, double added_value)
{
    if (added_value > 0)
        return (ceil(pos) - 0.299);
    else
        return (floor(pos) + 0.299);
}

int in_range(double angle)
{
    return (fabs(cos(angle * (M_PI / 180.0))) > sqrt(2) / 2);
}

void godirection(t_game *cub, t_player *player, double step, int direction, t_map *map)
{
    double added_x;
    double added_y;
    int safe_px;
    int safe_py;
    int edge_decision;
    
    edge_decision = 0;
    safe_px = cub->map->px + player->collisionmargin;
    safe_py = cub->map->py + player->collisionmargin;

	added_x = (step * direction) * cos(player->viewangle * (M_PI / 180.0));
	added_y = (step * direction) * sin(player->viewangle * (M_PI / 180.0));

    if (added_x < 0)
        safe_px = map->px + (player->collisionmargin * -1);
    if (added_y < 0)
        safe_py = map->py + (player->collisionmargin * -1);
    if (map->map[(int) map->py][(int) (safe_px)] == '0' && map->map[(int) (safe_py)][(int) map->px] == '0') 
        if (map->map[(int) (safe_py)][(int) (safe_px)] == '1')
            edge_decision = 1 + in_range(player->viewangle);
    if (edge_decision != 1)
    {
        if (map->map[(int) map->py][(int) (safe_px)] == '0')
            map->px += added_x;
        else
            map->px = adjust_colision(map->px, added_x);
    }
    if (edge_decision != 2)
    {
        if (map->map[(int) (safe_py)][(int) map->px] == '0')
            map->py += added_y;
        else
            map->py = adjust_colision(map->py, added_y);
    }
}

void	key_hook(t_game *cub, t_player *player, double frames_diff)
{
    double step;
    double turn;

    step = frames_diff * player->traverseperiod;
    turn = frames_diff * 360 / player->turnperiod;
	if (cub->keys.up == true)
        godirection(cub, player, step, 1, cub->map);
	if (cub->keys.down == true)
        godirection(cub, player, step, -1, cub->map);
	if (cub->keys.left == true)
        player->viewangle -= turn;
	if (cub->keys.right == true)
        player->viewangle += turn;
}