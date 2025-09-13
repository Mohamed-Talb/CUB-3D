#include "cub3d.h"

int main(int ac , char **av)
{
    (void)ac;
    t_game *cub;

    cub = ft_calloc(1, sizeof(t_game));
    parser(cub, av[1]);
    initgame(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
    mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);
}
