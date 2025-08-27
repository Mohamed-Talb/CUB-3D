#include "cub3d.h"

t_game *initgame()
{
    t_game *cub;

    cub = calloc(1, sizeof(t_game));
    cub->map = calloc(1, sizeof(t_map));
    cub->fov = 90;
    cub->view_angle = 45;
    cub->number_of_rays = WIDTH;
    cub->step = 0.1;
    ft_bzero(&cub->screen, sizeof(t_img));
    printf("kkkkkkkk\n");
    printf("kkkkkkkk\n");
    return cub;
}