#include "cub3d.h"



void coloring_screen(t_game *cub)
{
    int y;
    int x;
    int color;
    t_map *map;

    x = 0;
    y = 0;
    map = cub->map;
    color = create_trgb(0, map->c[0], map->c[1], map->c[1]);
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(&cub->screen, x, y, color);
            x++;
        }
        y++;
    }
    color = create_trgb(0, map->f[0], map->f[1], map->f[1]);
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(&cub->screen, x, y, color);
            x++;
        }
        y++;
    }
}




// void draw_column(t_game *cub, int start, int end, double dist)
// {
//     int y;
//     int lineh;
//     int linet;

//     (void) end;
//     if (dist <= 1)
//         lineh = HEIGHT;
//     else
//         lineh = HEIGHT / dist;
//     linet = (HEIGHT - lineh) / 2;
//     y = linet;
//     while (y < lineh + linet)
//     {
//         my_mlx_pixel_put(&cub->screen, start, y, 0x00323232);
//         y++;
//     }
// }
