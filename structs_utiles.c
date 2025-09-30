#include "cub3d.h"

void initaddr(t_game *cub)
{
    cub->textures->wall_ea.addr = mlx_get_data_addr(cub->textures->wall_ea.img,
                                &cub->textures->wall_ea.bits_per_pixel,
                                &cub->textures->wall_ea.line_length,
                                &cub->textures->wall_ea.endian);
    cub->textures->wall_we.addr = mlx_get_data_addr(cub->textures->wall_we.img,
                                &cub->textures->wall_we.bits_per_pixel,
                                &cub->textures->wall_we.line_length,
                                &cub->textures->wall_we.endian);
    cub->textures->wall_no.addr = mlx_get_data_addr(cub->textures->wall_no.img,
                                &cub->textures->wall_no.bits_per_pixel,
                                &cub->textures->wall_no.line_length,
                                &cub->textures->wall_no.endian);
    cub->textures->wall_so.addr = mlx_get_data_addr(cub->textures->wall_so.img,
                                &cub->textures->wall_so.bits_per_pixel,
                                &cub->textures->wall_so.line_length,
                                &cub->textures->wall_so.endian);
}

void initscreen(t_game *cub)
{
    cub->screen.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
    cub->screen.addr = mlx_get_data_addr(cub->screen.img,
                            &cub->screen.bits_per_pixel,
                            &cub->screen.line_length,
                            &cub->screen.endian);
}

t_game *initgame(t_game *cub)
{
    cub->textures = ft_calloc(1, sizeof(t_textures));
    if (!cub->textures)
        return (NULL);

    cub->mlx = mlx_init();
    if (cub->mlx == NULL)
        return (NULL);

    cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
    if (cub->win == NULL)
        return (NULL);
    initscreen(cub);
    cub->fov = 76;
    cub->nrays = WIDTH;
    cub->turn_period = 1.75;
    cub->traverse_period = 10;
    cub->plane_length = tan((cub->fov * M_PI / 180.0) / 2);

    // Screen image
    gettimeofday(&cub->frame_interval, NULL);
    return (cub);
}
