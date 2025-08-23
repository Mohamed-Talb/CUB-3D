#include "cub3d.h"

void print_game(const t_game *game)
{
    int i;

    if (!game || !game->map)
    {
        printf("Game or map is NULL\n");
        return;
    }
    printf("\n--- TEXTURES ---\n");
    printf("NO: %s\n", game->map->no ? game->map->no : "(null)");
    printf("SO: %s\n", game->map->so ? game->map->so : "(null)");
    printf("WE: %s\n", game->map->we ? game->map->we : "(null)");
    printf("EA: %s\n", game->map->ea ? game->map->ea : "(null)");
    
    printf("\n--- COLORS ---\n");
    if (game->map->f)
        printf("F: %d, %d, %d\n", game->map->f[0], game->map->f[1], game->map->f[2]);
    else
        printf("F: (null)\n");
    if (game->map->c)
        printf("C: %d, %d, %d\n", game->map->c[0], game->map->c[1], game->map->c[2]);
    else
        printf("C: (null)\n");

    printf("\n--- MAP ---\n");
    if (game->map->map)
    {
        for (i = 0; game->map->map[i]; i++)
            printf("%s\n", game->map->map[i]);
    }
    else
    {
        printf("(map is NULL)\n");
    }

    // printf("\n--- FILE (raw lines) ---\n");
    // if (game->file)
    // {
    //     for (i = 0; game->file[i]; i++)
    //         printf("%s\n", game->file[i]);
    // }
    // else
    // {
    //     printf("(file is NULL)\n");
    // }
}

int	destroy(t_game *cub)
{
	// free everything here and quit mlx safely
    (void) cub;
	exit(0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void go_direction(t_game *cub, int direction)
{
    double added_x;
    double added_y;

    added_x = (cub->step * direction) * cos(cub->view_angle * (M_PI / 180.0));
    added_y = (cub->step * direction) * sin(cub->view_angle * (M_PI / 180.0));
    if (cub->map->map[(int) (cub->player_y)][(int) (cub->player_x + added_x)] == '0')
        cub->player_x += added_x;
    // else
    //     cub->player_x = adjust_colision(player.x, added_x);
    if (cub->map->map[(int) (cub->player_y + added_y)][(int) (cub->player_x)] == '0')
        cub->player_y += added_y;
    // else
    //     cub->player_y = adjust_colision(player.y, added_y);
}

int	key_hook(int keysym, t_game *cub)
{
	if (keysym == XK_UP)
        go_direction(cub, 1);
    else if (keysym == XK_DOWN)
        go_direction(cub, -1);
	else if (keysym == XK_LEFT)
        cub->view_angle -= 4;
	else if (keysym == XK_RIGHT)
        cub->view_angle += 4;
	else if (keysym == ESC)
		(destroy(cub));
	return (0);
}

void set_initial_values(t_game *cub)
{
    cub->player_x = 1.2;
    cub->player_y = 1.2;
    cub->fov = 90;
    cub->view_angle = 45;
    cub->number_of_rays = WIDTH;
    cub->step = 0.1;
}

void draw_screen_column(t_game *cub, int start, int end, double dist)
{
    int line_height;
    int line_tail;

    (void) end;
    if (dist <= 1)
        line_height = HEIGHT;
    else
        line_height = (int) HEIGHT / dist;
    line_tail = (int) (HEIGHT - line_height) / 2;
    for (int y = line_tail; y < line_height + line_tail; y++)
        my_mlx_pixel_put(&cub->screen, start, y, 0x00323232);
}

void draw_all_lines(t_game *cub)
{
    double column_angle;
    double ray_angle;
    t_ray ray;

    column_angle = cub->fov / cub->number_of_rays;
    for (int i = 0; i < cub->number_of_rays; i++)
    {
        ray_angle = (i * column_angle) + column_angle + cub->view_angle;
        ray = dda(cub->map, ray_angle - (cub->fov / 2), cub->player_x, cub->player_y);
        draw_screen_column(cub, i, i, ray.distance);
    }
}

int	render_next_frame(t_game *cub)
{
	cub->draw_frame++;
    // printf("draw_frame is: %d\n", cub->draw_frame);
	// if (cub->draw_frame > 2)
    // {
        // render 1 frame here
        // printf("player_x: %lf, player_y: %lf\n", cub->player_x, cub->player_y);
        if (cub->screen.img == NULL)
        {
            cub->screen.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
            cub->screen.addr = mlx_get_data_addr(cub->screen.img, &cub->screen.bits_per_pixel, &cub->screen.line_length,
								&cub->screen.endian);
        }
        // clear window with flore + ceiling color for now
        for (int y = 0; y < HEIGHT; y++)
            for (int x = 0; x < WIDTH; x++)
                my_mlx_pixel_put(&cub->screen, x, y, 0x00d2d2d2);
        // draw_screen_column(cub, 10, 10, 7);
        draw_all_lines(cub);
        mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
		// cub->draw_frame = 0;
        // print_mem_usage();
    // }
    return (0);
}

int main(int ac , char **av)
{
    (void)ac;
    t_game *cub = NULL;
    initgame(&cub);
    parser(cub, av[1]);
    ft_bzero(&cub->screen, sizeof(t_img)); // because parser touches the screen variable for some reason
    // printf("first img is: %p\n", cub->screen.img);
    set_initial_values(cub);
    cub->map->map[1][1] = '0';
    print_game(cub);
    // dda(cub->map, 45);
    cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		return (EXIT_FAILURE); // free first!!!
    cub->win = mlx_new_window(cub->mlx, WIDTH,
        HEIGHT, "Cub3D");
	if (cub->win == NULL)
		return (EXIT_FAILURE); // free first !!!
    mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
    mlx_hook(cub->win, 17, 1L << 17, destroy, cub);
    mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);
}
