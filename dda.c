#include "cub3d.h"

#define M_PI 3.14159265358979323846

void initdda(t_dda *dda)
{
    dda->mapx = (int)dda->posx; 
    dda->mapy = (int)dda->posy;
    dda->deltadistx = fabs(1 / dda->rayx); 
    dda->deltadisty = fabs(1 / dda->rayy);
    if (dda->rayx < 0)
    {
        dda->stepx = -1;
        dda->sidedistx = (dda->posx - dda->mapx) * dda->deltadistx;
    }
    else
    {
        dda->stepx = 1;
        dda->sidedistx = (dda->mapx + 1.0 - dda->posx) * dda->deltadistx;
    }
    if (dda->rayy < 0)
    {
        dda->stepy = -1;
        dda->sidedisty = (dda->posy - dda->mapy) * dda->deltadisty;
    }
    else
    {
        dda->stepy = 1;
        dda->sidedisty = (dda->mapy + 1.0 - dda->posy) * dda->deltadisty;
    }
}

void hitwall(t_dda *dda, int side, t_ray *ray)
{
    if (side == 0)
    {
        ray->distance = (dda->sidedistx - dda->deltadistx);
        ray->wallx = dda->posy + ray->distance * dda->rayy;
    }
    else
    {
        ray->distance = (dda->sidedisty - dda->deltadisty);
        ray->wallx = dda->posx + ray->distance * dda->rayx;
    }
}

t_ray dda(t_game *cub, double ray_dir_x, double ray_dir_y)
{
    t_dda dda;
    t_ray ray;
    int hit; // probably could be removed

    hit = 0;
    dda.posx = cub->map->px; // repetitive, to be removed
    dda.posy = cub->map->py; // repetitive, to be removed
    dda.rayx = ray_dir_x;
    dda.rayy = ray_dir_y;
    ray.side = 0;
    initdda(&dda);
    while (hit == 0)
    {
        if (dda.sidedistx < dda.sidedisty)
        {
            dda.sidedistx += dda.deltadistx;
            dda.mapx += dda.stepx;
            ray.side = 0;
        }
        else
        {
            dda.sidedisty += dda.deltadisty;
            dda.mapy += dda.stepy;
            ray.side = 1;
        }
        if (cub->map->map[dda.mapy][dda.mapx] == '1')
            hit = 1;
    }
    hitwall(&dda, ray.side, &ray);
    ray.rayx = dda.rayx;
    ray.rayy = dda.rayy;
    return (ray);
}
