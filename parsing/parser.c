#include "../cub3d.h"

void initeyes(t_game *cub)
{
    char pl;
    int  px;
    int  py;

    px = cub->map->px;
    py = cub->map->py;
    pl = cub->map->map[py][px];
    if (pl == 'N')
        cub->player->viewangle = -90;   // Facing North
    else if (pl == 'S')
        cub->player->viewangle = 90;  // Facing South
    else if (pl == 'E')
        cub->player->viewangle = 0;    // Facing East
    else if (pl == 'W')
        cub->player->viewangle = 180;  // Facing West
    cub->map->map[py][px] = '0';
}

void parser(t_game *cub, char *file)
{
    filecontent(cub, file);
    components(cub); 
    parsemap(cub);
    cub->map->m_height = ft_strlen2(cub->map->map);
    mapvalidation(cub->map);
    checkwalls(cub->map);
    initeyes(cub);
}
