#include "cub3d.h"


double adjust_colision(double pos, double added_value)
{
    if (added_value > 0)
        return (ceil(pos) - 0.299);
    else
        return (floor(pos) + 0.299);
}


void collision(t_map *map, t_move move)
{
    if (move.edge_decision != 1)
    {
        if (map->map[(int)map->py][(int)move.safe_px] == '0')
            map->px += move.added_x;
        else
            map->px = adjust_colision(map->px, move.added_x);
    }
    if (move.edge_decision != 2)
    {
        if (map->map[(int)move.safe_py][(int)map->px] == '0')
            map->py += move.added_y;
        else
            map->py = adjust_colision(map->py, move.added_y);
    }
}