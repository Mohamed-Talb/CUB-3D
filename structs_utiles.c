#include "cub3d.h"

void initgame(t_game **cub)
{
    *cub = ft_calloc(1, sizeof(t_game));
    (*cub)->map = ft_calloc(1, sizeof(t_map)); 
    return ;
}