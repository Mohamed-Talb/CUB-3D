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

void init_textures(t_game *cub)
{
    char **texnames;

    texnames = cub->map->tpaths;
    cub->textures->wall_no.img = mlx_xpm_file_to_image(cub->mlx, texnames[0],
                        &cub->textures->wall_no.wdt,
                        &cub->textures->wall_no.hgt);
    cub->textures->wall_so.img = mlx_xpm_file_to_image(cub->mlx, texnames[1],
                        &cub->textures->wall_so.wdt,
                        &cub->textures->wall_so.hgt);
    cub->textures->wall_we.img = mlx_xpm_file_to_image(cub->mlx, texnames[2],
                        &cub->textures->wall_we.wdt,
                        &cub->textures->wall_we.hgt);
    cub->textures->wall_ea.img = mlx_xpm_file_to_image(cub->mlx, texnames[3],
                        &cub->textures->wall_ea.wdt,
                        &cub->textures->wall_ea.hgt);
    if ((!cub->textures->wall_no.img) || (!cub->textures->wall_so.img) || (!cub->textures->wall_we.img) || (!cub->textures->wall_ea.img))
    {
        printf("Failed to load texture:\n");
        exit(1);
    }
}

void initplayer(t_game *cub)
{
    cub->player->fov = 75;
    cub->player->turnperiod = 1.75;
    cub->player->traverseperiod = 8;
    cub->player->collisionmargin = 0.3;
    cub->player->plane = tan((cub->player->fov * M_PI / 180.0) / 2);
}

// function needs more error handling
t_game *initgame(t_game *cub)
{
    cub->nrays = WIDTH;
    cub->mlx = mlx_init();
    if (cub->mlx == NULL)
        return (NULL); // free and exit
    cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
    if (cub->win == NULL)
        return (NULL); // free and exit
    initscreen(cub);
    init_textures(cub);
    initaddr(cub);
    initplayer(cub);
    gettimeofday(&cub->frame_interval, NULL);
    return (cub);
}
