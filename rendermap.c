#include "cub3d.h"

void draw_lines(t_game *cub)
{
    int		x;
    t_ray  ray;
    double wallx;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double ray_dir_x;
    double ray_dir_y;
    double camera_x;

    x = 0;
    dir_x = cos(cub->player->viewangle * M_PI / 180.0);
    dir_y = sin(cub->player->viewangle * M_PI / 180.0);
    plane_x = -dir_y * cub->player->plane;
    plane_y = dir_x * cub->player->plane;
	while(x < cub->nrays)
    {
        camera_x = 2 * x / ((float) WIDTH) - 1;
        ray_dir_x = dir_x + plane_x * camera_x;
        ray_dir_y = dir_y + plane_y * camera_x;
        ray = dda(cub, ray_dir_x, ray_dir_y);
        if (ray.side == 0)
            wallx = ray.cor[1];
        else
            wallx = ray.cor[0];
        drawcolum(cub, x, ray.distance, wallx, &ray);
		x++;
    }
}

int	render_next_frame(t_game *cub)
{
    double frames_diff;
    struct timeval	current;

    gettimeofday(&current, NULL);
    frames_diff = get_timestamp(current, cub->frame_interval);
    cub->frame_interval = current;
    key_hook(cub, frames_diff);
    draw_lines(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    return (0);
}
