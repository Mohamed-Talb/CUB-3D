#include "cub3d.h"


void drawwall(t_game *cub, int x, int y)
{
    int i = x;
    int j = y;
    while (i <= 32)
    {
        j = y;
        while(j <= 32)
        {
            mlx_pixel_put(cub->mlx, cub->win, i, j, 0xff0000);
            j++;
        }
        i++;
    }
}

void rendermap(t_game *cub)
{
    int x = 0;
    int y = 0;
    t_map *map = cub->map;
    while(x < map->m_width)
    {
        y = 0;
        while (y < map->m_height)
        {
            if(map->map[y][x] == '1')
            {
                drawwall(cub, x, y);
            }
            y++;
        }
        x++;
    } 

}