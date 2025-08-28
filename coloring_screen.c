#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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