#include "cub3d.h"

int	destroy(t_game *cub)
{
    // free
    (void) cub;
	exit(0);
}

void godirection(t_game *cub, int direction, t_map *map)
{
	int new_px;
    int new_py;
    double added_x;
    double added_y;
	
	added_x = (cub->step * direction) * cos(cub->view_angle * (M_PI / 180.0));
	added_y = (cub->step * direction) * sin(cub->view_angle * (M_PI / 180.0));
    new_px = (int)(map->px + added_x);
    new_py = (int)(map->py + added_y);
    if (map->map[(int) map->py][new_px] == '0')
        map->px += added_x;
    if (map->map[new_py][(int) map->px] == '0')
        map->py += added_y;
}

void	key_hook(t_game *cub)
{
	if (cub->keys.up == true)
    {
        godirection(cub, 1, cub->map);
    }
    if (cub->keys.down == true)
    {
        godirection(cub, -1, cub->map);
    }
	if (cub->keys.left == true)
    {
        cub->view_angle -= cub->turn_angle;
        // printf("turn angle is: %f\n", cub->turn_angle);
        // exit(0);
    }
	if (cub->keys.right == true)
    {
        cub->view_angle += cub->turn_angle;
        // printf("turn angle is: %f\n", cub->turn_angle);
        // exit(0);
    }
}

// int	key_hook(int keysym, t_game *cub)
// {
// 	if (keysym == XK_UP)
//         godirection(cub, 1, cub->map);
//     else if (keysym == XK_DOWN)
//         godirection(cub, -1, cub->map);
// 	else if (keysym == XK_LEFT)
//         cub->view_angle -= 4;
// 	else if (keysym == XK_RIGHT)
//         cub->view_angle += 4;
// 	else if (keysym == ESC)
// 		(destroy(cub));
// 	return (0);
// }

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

long	time_to_long(struct timeval timestamp)
{
	return (timestamp.tv_sec * 1000000 + timestamp.tv_usec);
}

int	get_timestamp(struct timeval *begining)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((time_to_long(current) - time_to_long(*begining)) / 1000);
}

bool fps_handler(struct timeval *begining, int frequency)
{
    if (get_timestamp(begining) >= 1000 / frequency)
        return true;
    return false;
}

int	render_next_frame(t_game *cub)
{
    if (fps_handler(&cub->frame_interval, 60))
    {
        draw_lines(cub);
        mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
        key_hook(cub);
    }
    return (0);
}
