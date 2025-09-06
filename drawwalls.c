#include "cub3d.h"

static void get_column_limits(int lineh, int *starty, int *endy)
{
    *starty = (HEIGHT - lineh) / 2;
    if (*starty < 0)
        *starty = 0;
    *endy = *starty + lineh;
    if (*endy >= HEIGHT)
        *endy = HEIGHT - 1;
}

static t_img *select_texture(t_game *cub, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->rayx > 0)
            return &cub->textures->wall_we;
        else
            return &cub->textures->wall_ea;
    }
    else
    {
        if (ray->rayy > 0)
            return &cub->textures->wall_no;
        else
            return &cub->textures->wall_so;
    }
}

static void draw_ceiling(t_game *cub, int x, int starty)
{
    int y = 0;
    int color = create_trgb(0, cub->map->c[0], cub->map->c[1], cub->map->c[2]);
    while (y < starty)
    {
        my_mlx_pixel_put(&cub->screen, x, y, color);
        y++;
    }
}

static void draw_floor(t_game *cub, int x, int endy)
{
    int y = endy + 1;
    int color = create_trgb(0, cub->map->f[0], cub->map->f[1], cub->map->f[2]);
    while (y < HEIGHT)
    {
        my_mlx_pixel_put(&cub->screen, x, y, color);
        y++;
    }
}

void draw_column(t_game *cub, int x, double dist, double wallx, t_ray *ray)
{
    int lineh;
    int starty, endy;
    t_img *texture;
    int texx;

    if (dist == 0)
        lineh = HEIGHT;
    else
        lineh = (HEIGHT / dist);
    lineh *= 1.5;
    get_column_limits(lineh, &starty, &endy);
    texture = select_texture(cub, ray);
    texx = (int)(wallx * texture->wdt);
    draw_ceiling(cub, x, starty);
    int y = starty;
    starty = (HEIGHT - lineh) / 2;
    int texy;
    int color;
    while (y <= endy)
    {
        texy = (y - starty) * texture->hgt / lineh;
        color = get_pixel_from_texture(texture, texx, texy);
        my_mlx_pixel_put(&cub->screen, x, y, color);
        y++;
    }
    printf("texy is: %d\n", texy);
    draw_floor(cub, x, endy);
}
