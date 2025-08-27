#include "cub3d.h"

int	destroy(t_game *cub)
{
    // free
    (void) cub;
	exit(0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void draw_column(t_game *cub, int start, int end, double dist)
{
    int y;
    int lineh;
    int linet;

    (void) end;
    if (dist <= 1)
        lineh = HEIGHT;
    else
        lineh = HEIGHT / dist;
    linet = (HEIGHT - lineh) / 2;
    y = linet;
    while (y < lineh + linet)
    {
        my_mlx_pixel_put(&cub->screen, start, y, 0x00323232);
        y++;
    }
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
        draw_column(cub, i, i, ray.distance);
		i++;
    }
}

int	render_next_frame(t_game *cub)
{
	int x;
	int y;

    cub->draw_frame++;
    if (cub->screen.img == NULL)
    {
        cub->screen.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
        cub->screen.addr = mlx_get_data_addr(cub->screen.img,
                            &cub->screen.bits_per_pixel,
                            &cub->screen.line_length,
                            &cub->screen.endian);
    }
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(&cub->screen, x, y, 0x00d2d2d2);
            x++;
        }
        y++;
    }
    draw_lines(cub, cub->map);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
    return (0);
}
