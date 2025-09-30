#include "cub3d.h"

int	destroy(t_game *cub)
{
    // free
    (void) cub;
	exit(0);
}

void godirection(t_game *cub, double step, int direction, t_map *map)
{
	int new_px;
    int new_py;
    double added_x;
    double added_y;
	
	added_x = (step * direction) * cos(cub->view_angle * (M_PI / 180.0));
	added_y = (step * direction) * sin(cub->view_angle * (M_PI / 180.0));
    new_px = (int)(map->px + added_x);
    new_py = (int)(map->py + added_y);
    if (map->map[(int) map->py][new_px] == '0')
        map->px += added_x;
    if (map->map[new_py][(int) map->px] == '0')
        map->py += added_y;
}

void	key_hook(t_game *cub, double frames_diff)
{
    double step;
    double turn;

    step = frames_diff * cub->traverse_period;
    turn = frames_diff * 360 / cub->turn_period;
	if (cub->keys.up == true)
        godirection(cub, step, 1, cub->map);
	if (cub->keys.down == true)
        godirection(cub, step, -1, cub->map);
	if (cub->keys.left == true)
        cub->view_angle -= turn;
	if (cub->keys.right == true)
        cub->view_angle += turn;
}

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
    dir_x = cos(cub->view_angle * M_PI / 180.0);
    dir_y = sin(cub->view_angle * M_PI / 180.0);
    plane_x = -dir_y * cub->plane_length;
    plane_y = dir_x * cub->plane_length;
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
