#include "../cub3d.h"

void parsemap(t_game *cub)
{
    // int i = 0;
    cub->map->map = ft_strdup2(cub->file);
    if(cub->map->map == NULL)
    {
        // errors
        return ;
    }
}