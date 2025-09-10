#include "cub3d.h"

// void print_game(const t_game *game)
// {
//     int i;

//     if (!game || !game->map)
//     {
//         printf("Game or map is NULL\n");
//         return;
//     }
//     printf("\n--- TEXTURES ---\n");
//     printf("NO: %s\n", game->map->no ? game->map->no : "(null)");
//     printf("SO: %s\n", game->map->so ? game->map->so : "(null)");
//     printf("WE: %s\n", game->map->we ? game->map->we : "(null)");
//     printf("EA: %s\n", game->map->ea ? game->map->ea : "(null)");
    
//     printf("\n--- COLORS ---\n");
//     if (game->map->f)
//         printf("F: %d, %d, %d\n", game->map->f[0], game->map->f[1], game->map->f[2]);
//     else
//         printf("F: (null)\n");
//     if (game->map->c)
//         printf("C: %d, %d, %d\n", game->map->c[0], game->map->c[1], game->map->c[2]);
//     else
//         printf("C: (null)\n");

//     printf("\n--- MAP ---\n");
//     if (game->map->map)
//     {
//         for (i = 0; game->map->map[i]; i++)
//             printf("%s\n", game->map->map[i]);
//     }
//     else
//         printf("(map is NULL)\n");
// }






int main(int ac , char **av)
{
    (void)ac;
    t_game *cub;

    cub = ft_calloc(1, sizeof(t_game));
    parser(cub, av[1]);
    // print_game(cub);
    initgame(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
    mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);
}
