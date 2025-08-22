#include "../cub3d.h"

void parser(t_game *cub, char *file)
{
    filecontent(cub, file);
    textures(cub);
    colors(cub);
    parsemap(cub);
    cub->map->m_height = ft_strlen2(cub->map->map);
    checkwalls(cub->map);
    checkelements(cub->map);
}
