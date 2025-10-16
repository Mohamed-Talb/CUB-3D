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