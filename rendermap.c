#include "cub3d.h"

int	destroy(t_game *cub)
{
    // free
    (void) cub;
	exit(0);
}


void go_direction(t_game *cub, int direction, t_map *map)
{
	int new_px;
    int new_py;
    int cur_px;
    int cur_py;
    double added_x;
    double added_y;
	
	added_x = (cub->step * direction) * cos(cub->view_angle * (M_PI / 180.0));
	added_y = (cub->step * direction) * sin(cub->view_angle * (M_PI / 180.0));
    new_px = (int)(map->px + added_x);
    new_py = (int)(map->py + added_y);
    cur_px = (int)(map->px);
    cur_py = (int)(map->py);
    if (map->map[cur_py][new_px] == '0')
        map->px += added_x;
    if (map->map[new_py][cur_px] == '0')
        map->py += added_y;
}


int	key_hook(int keysym, t_game *cub)
{
	if (keysym == XK_UP)
        go_direction(cub, 1, cub->map);
    else if (keysym == XK_DOWN)
        go_direction(cub, -1, cub->map);
	else if (keysym == XK_LEFT)
        cub->view_angle -= 4;
	else if (keysym == XK_RIGHT)
        cub->view_angle += 4;
	else if (keysym == ESC)
		(destroy(cub));
	return (0);
}


void draw_lines(t_game *cub, t_map *map)
{
    double cangle;
    double rangle;
	int		i;
    t_ray  ray;

    cangle = cub->fov / cub->number_of_rays;
    i = 0;
	while(i < cub->number_of_rays)
    {
        rangle = (i * cangle) + cangle + cub->view_angle;
		rangle = rangle - (cub->fov / 2);
        ray = dda(map, rangle, map->px, map->py);
        double angle_diff = rangle - cub->view_angle;
        double corrected_dist = ray.distance * cos(angle_diff * (M_PI / 180.0));
        double wallx;
        if (ray.side == 0)
            wallx = ray.cor[1];
        else
            wallx = ray.cor[0];
        draw_column(cub, i, corrected_dist, wallx, &ray);
		i++;
    }
}

int	render_next_frame(t_game *cub)
{
    cub->draw_frame++;

    // coloring_screen(cub);
    draw_lines(cub, cub->map);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    return (0);
}