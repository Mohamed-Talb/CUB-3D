#include "../cub3d.h"

void initeyes(t_game *cub)
{
    char player;
    int  px;
    int  py;

    px = cub->map->px;
    py = cub->map->py;
    player = cub->map->map[py][px];

    if (player == 'N')
        cub->view_angle = 90;   // Facing North
    else if (player == 'S')
        cub->view_angle = 270;  // Facing South
    else if (player == 'E')
        cub->view_angle = 0;    // Facing East
    else if (player == 'W')
        cub->view_angle = 180;  // Facing West
    cub->map->map[py][px] = '0';
}

void parser(t_game *cub, char *file)
{
    cub->map = ft_calloc(1, sizeof(t_map));
    filecontent(cub, file);
    components(cub);
    parsemap(cub);
    cub->map->m_height = ft_strlen2(cub->map->map);
    mapvalidation(cub->map);
    checkwalls(cub->map);
    initeyes(cub);
}
