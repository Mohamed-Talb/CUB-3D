
#include "cub3d.h"
#define TILE_SIZE 10

t_game *initgame(t_game *cub)
{
    cub->textures = ft_calloc(1, sizeof(t_textures));
    if (!cub->textures)
        return (NULL);

    cub->mlx = mlx_init();
    if (cub->mlx == NULL)
        return (NULL);

    cub->win = mlx_new_window(cub->mlx, cub->map->m_width * TILE_SIZE, cub->map->m_height * TILE_SIZE, "Cub3D");
    if (cub->win == NULL)
        return (NULL);

    // Screen image
    return cub;
}



void drawwall(t_game *cub, int x, int y, int color)
{
    int i = x * TILE_SIZE;
    int j;
    while (i < (x + 1) * TILE_SIZE)
    {
        j = y * TILE_SIZE;
        while (j < (y + 1) * TILE_SIZE)
        {
            mlx_pixel_put(cub->mlx, cub->win, i, j, color);
            j++;
        }
        i++;
    }
}

void drawcircle(int cx, int cy, float r, t_game *cub)
{
    float x = 0;
    float y = -r;
    double midy = 0.0;
    while(x < -y)
    {
        midy = y + 0.5;
        if (x*x + midy*midy >= r*r)
            y++;
        mlx_pixel_put(cub->mlx, cub->win, (cx + x), (cy + y), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx - x), (cy + y), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx + x), (cy - y), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx - x), (cy - y), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx + y), (cy + x), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx - y), (cy + x), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx + y), (cy - x), 0x0000ff);
        mlx_pixel_put(cub->mlx, cub->win, (cx - y), (cy - x), 0x0000ff);
        x++;
    }
}


void rendermap(t_game *cub)
{
    int x = 0;
    int y = 0;
    t_map *map = cub->map;
    while(y < map->m_height)
    {
        x = 0;
        // printf("%d\n", map->m_width);
        // printf("%d\n", map->m_height);
        while (map->map[y][x])
        {
            if(map->map[y][x] == '1')
            {
                drawwall(cub, x, y, 0xff0000);
            }

            x++;
        }
        y++;
    } 
    int px = (int)cub->map->px * TILE_SIZE + TILE_SIZE / 2;
    int py = (int)cub->map->py  * TILE_SIZE + TILE_SIZE / 2;
    float i = 0;
    while (i < 16)
    {
        drawcircle(px, py, i, cub);
        i += 0.01;
    }
    // drawcircle(px, py, TILE_SIZE / 2 - 2, cub);
    // drawwall(cub, (int)cub->player_x, (int)cub->player_y, 0xffffff);

}


int main(int ac , char **av)
{
    (void)ac;
    t_game *cub;

    cub = ft_calloc(1, sizeof(t_game));
    parser(cub, av[1]);
    // print_game(cub);
    initgame(cub);
    rendermap(cub);
    // int x = 0;
    // int y = 0;
    // mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    // mlx_put_image_to_window(cub->mlx,cub->win, cub->textures->wall_ea, 0, 0);
    // mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
    // mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    // mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);
}