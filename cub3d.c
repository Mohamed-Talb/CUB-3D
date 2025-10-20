#include "cub3d.h"

int	destroy(t_game *cub)
{
    (void) cub;
    if (cub->textures->wall_no.img)
	{
		mlx_destroy_image(cub->mlx, cub->textures->wall_no.img);
		mlx_destroy_image(cub->mlx, cub->textures->wall_so.img);
		mlx_destroy_image(cub->mlx, cub->textures->wall_we.img);
		mlx_destroy_image(cub->mlx, cub->textures->wall_ea.img);
	}
    if (cub->screen.img)
		mlx_destroy_image(cub->mlx, cub->screen.img);
    if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
    if (cub->mlx)
    {
        mlx_destroy_display(cub->mlx);
        free(cub->mlx);
    }
    free_all_adresses();
	exit(0);
}

t_game *getmemory()
{
    t_game *cub;

    cub = ft_calloc(1, sizeof(t_game));
    cub->map = ft_calloc(1, sizeof(t_map));
    cub->player = ft_calloc(1, sizeof(t_player));
    cub->map->tpaths = ft_calloc(4, sizeof(char *));
    cub->textures = ft_calloc(1, sizeof(t_textures));
    return (cub);
}

int main(int ac , char **av)
{
    (void)ac;
    t_game *cub;
   
    cub = getmemory();
    parser(cub, av[1]);
    initgame(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    mlx_hook(cub->win, 2, 1L << 0, set_key_press, cub);
    mlx_hook(cub->win, 3, 1L << 1, set_key_release, cub);
    mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    mlx_loop_hook(cub->mlx, render_frame, cub);
    mlx_loop(cub->mlx);
}
