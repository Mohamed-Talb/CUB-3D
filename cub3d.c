#include "cub3d.h"

int	set_key_press(int keysym, t_game *cub)
{
    if (keysym == XK_UP)
        cub->keys.up = true;
    else if (keysym == XK_DOWN)
        cub->keys.down = true;
	else if (keysym == XK_LEFT)
        cub->keys.left = true;
	else if (keysym == XK_RIGHT)
        cub->keys.right = true;
	else if (keysym == ESC)
		(destroy(cub));
    return (0);
}

int	set_key_release(int keysym, t_game *cub)
{
    if (keysym == XK_UP)
        cub->keys.up = false;
    else if (keysym == XK_DOWN)
        cub->keys.down = false;
    else if (keysym == XK_LEFT)
        cub->keys.left = false;
    else if (keysym == XK_RIGHT)
        cub->keys.right = false;
    return (0);
}

t_game *getmemory()
{
    t_game *cub;

    cub = ft_calloc(1, sizeof(t_game));
    // cub->keys;
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
    // mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
    mlx_hook(cub->win, 2, 1L << 0, set_key_press, cub);
    mlx_hook(cub->win, 3, 1L << 1, set_key_release, cub);
    mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);
}
