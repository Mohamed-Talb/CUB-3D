#include "cub3d.h"

int	destroy(t_game *cub)
{
    // free
    (void) cub;
	exit(0);
}

double adjust_colision(double pos, double added_value)
{
    if (added_value > 0)
        return (ceil(pos) - 0.299);
    else
        return (floor(pos) + 0.299);
}

int in_range(double angle)
{
    return (fabs(cos(angle * (M_PI / 180.0))) > sqrt(2) / 2);
}

void godirection(t_game *cub, double step, int direction, t_map *map)
{
    double added_x;
    double added_y;
    int safe_px;
    int safe_py;
    int edge_decision;
    
    edge_decision = 0;
    safe_px = map->px + cub->collisionMargin;
    safe_py = map->py + cub->collisionMargin;
	added_x = (step * direction) * cos(cub->view_angle * (M_PI / 180.0));
	added_y = (step * direction) * sin(cub->view_angle * (M_PI / 180.0));
    if (added_x < 0)
        safe_px = map->px + (cub->collisionMargin * -1);
    if (added_y < 0)
        safe_py = map->py + (cub->collisionMargin * -1);
    if (map->map[(int) map->py][(int) (safe_px)] == '0'
        && map->map[(int) (safe_py)][(int) map->px] == '0'
        && map->map[(int) (safe_py)][(int) (safe_px)] == '1')
        edge_decision = 1 + in_range(cub->view_angle);
    if (edge_decision != 1)
    {
        if (map->map[(int) map->py][(int) (safe_px)] == '0')
            map->px += added_x;
        else
            map->px = adjust_colision(map->px, added_x);
    }
    if (edge_decision != 2)
    {
        if (map->map[(int) (safe_py)][(int) map->px] == '0')
            map->py += added_y;
        else
            map->py = adjust_colision(map->py, added_y);
    }
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
