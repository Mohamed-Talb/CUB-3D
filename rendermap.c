#include "cub3d.h"

void drawlines(t_game *cub)
{
    t_draw draw;
    int x;

    x = 0;
    draw.dir_x = cos(cub->player->viewangle * M_PI / 180.0);
    draw.dir_y = sin(cub->player->viewangle * M_PI / 180.0);
    draw.plane_x = -draw.dir_y * cub->player->plane;
    draw.plane_y =  draw.dir_x * cub->player->plane;

    while (x < cub->nrays)
    {
        draw.camera_x = 2 * x / ((float) WIDTH) - 1;
        draw.ray_dir_x = draw.dir_x + draw.plane_x * draw.camera_x;
        draw.ray_dir_y = draw.dir_y + draw.plane_y * draw.camera_x;
        draw.ray = dda(cub, draw.ray_dir_x, draw.ray_dir_y);
        drawcolum(cub, x, draw.ray.distance, draw.ray.wallx, &draw.ray);
        x++;
    }
}

int	render_frame(t_game *cub)
{
    double fdiff;
    struct timeval	current;

    gettimeofday(&current, NULL);
    fdiff = get_timestamp(current, cub->frame_interval);
    cub->frame_interval = current;
    key_hook(cub, fdiff);
    drawlines(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    return (0);
}
