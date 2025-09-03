#include "cub3d.h"

void print_game(const t_game *game)
{
    int i;

    if (!game || !game->map)
    {
        printf("Game or map is NULL\n");
        return;
    }
    printf("\n--- TEXTURES ---\n");
    printf("NO: %s\n", game->map->no ? game->map->no : "(null)");
    printf("SO: %s\n", game->map->so ? game->map->so : "(null)");
    printf("WE: %s\n", game->map->we ? game->map->we : "(null)");
    printf("EA: %s\n", game->map->ea ? game->map->ea : "(null)");
    
    printf("\n--- COLORS ---\n");
    if (game->map->f)
        printf("F: %d, %d, %d\n", game->map->f[0], game->map->f[1], game->map->f[2]);
    else
        printf("F: (null)\n");
    if (game->map->c)
        printf("C: %d, %d, %d\n", game->map->c[0], game->map->c[1], game->map->c[2]);
    else
        printf("C: (null)\n");

    printf("\n--- MAP ---\n");
    if (game->map->map)
    {
        for (i = 0; game->map->map[i]; i++)
            printf("%s\n", game->map->map[i]);
    }
    else
        printf("(map is NULL)\n");
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

    // Screen image
    if (cub->screen.img == NULL)
    {
        cub->screen.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
        cub->screen.addr = mlx_get_data_addr(cub->screen.img,
                                &cub->screen.bits_per_pixel,
                                &cub->screen.line_length,
                                &cub->screen.endian);
    }

    cub->fov = 90;
    cub->view_angle = 45;
    cub->number_of_rays = WIDTH;
    cub->step = 0.1;

    cub->textures->wall_ea.img = mlx_xpm_file_to_image(cub->mlx, cub->map->ea,
                                &cub->textures->wall_ea.wdt,
                                &cub->textures->wall_ea.hgt);
    cub->textures->wall_we.img = mlx_xpm_file_to_image(cub->mlx, cub->map->we,
                                &cub->textures->wall_we.wdt,
                                &cub->textures->wall_we.hgt);
    cub->textures->wall_no.img = mlx_xpm_file_to_image(cub->mlx, cub->map->no,
                                &cub->textures->wall_no.wdt,
                                &cub->textures->wall_no.hgt);
    cub->textures->wall_so.img = mlx_xpm_file_to_image(cub->mlx, cub->map->so,
                                &cub->textures->wall_so.wdt,
                                &cub->textures->wall_so.hgt);
    if (!cub->textures->wall_so.img || !cub->textures->wall_ea.img || !cub->textures->wall_we.img || !cub->textures->wall_no.img)
    {
        printf("Failed to load South texture: %s\n", cub->map->so);
        exit(1);
    }
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
    return cub;
}





int main(int ac , char **av)
{
    (void)ac;
    t_game *cub;

    cub = ft_calloc(1, sizeof(t_game));
    parser(cub, av[1]);
    print_game(cub);
    initgame(cub);
    // int x = 0;
    // int y = 0;
    // mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    // mlx_put_image_to_window(cub->mlx,cub->win, cub->textures->wall_ea, 0, 0);
    mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
    mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);
}




