#include "cub3d.h"

// #define MAP_WIDTH 8
// #define MAP_HEIGHT 8
#define M_PI 3.14159265358979323846

// int worldMap[MAP_HEIGHT][MAP_WIDTH] =
// {
//     {1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,1},
//     {1,0,1,0,1,0,0,1},
//     {1,0,1,0,0,0,0,1},
//     {1,0,0,0,1,1,0,1},
//     {1,0,1,0,0,0,0,1},
//     {1,0,0,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1},
// };


typedef struct s_dda
{
    double posx;
    double posy;
    double rayx;
    double rayy;
    double sidedisty;
    double sidedistx;
    double deltadisty;
    double deltadistx;
    int mapx;
    int mapy;
    int stepx;
    int stepy;
} t_dda;

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

t_ray *hitwall(t_dda *dda, int side, t_ray *ray)
{
    double walldist;
    double hitx;
    double hity;

    if (side == 0)
    {
        walldist = dda->sidedistx - dda->deltadistx;
        hitx = dda->mapx;
        if (dda->stepx < 0)
            hitx += 1.0;
        hity = dda->posy + walldist * dda->rayy;
    }
    else
    {
        walldist = dda->sidedisty - dda->deltadisty;
        hity = dda->mapy;
        if (dda->stepy < 0)
            hity += 1.0;
        hitx = dda->posx + walldist * dda->rayx;
    }
    ray->distance = walldist;
    ray->cor[0] = hitx;             
    ray->cor[1] = hity;             
    ray->side = side;
    return ray;
}

t_ray dda(t_game *cub, double ray_dir_x, double ray_dir_y)
{
    t_dda dda;
    t_ray ray;
    int side;
    int hit;

    hit = 0;
    dda.posx = cub->map->px; // repetitive, to be removed
    dda.posy = cub->map->py; // repetitive, to be removed
    dda.rayx = ray_dir_x;
    dda.rayy = ray_dir_y;
    side = 0;
    initdda(&dda);
    while (hit == 0)
    {
        if (dda.sidedistx < dda.sidedisty)
        {
            dda.sidedistx += dda.deltadistx;
            dda.mapx += dda.stepx;
            side = 0;
        }
        else
        {
            dda.sidedisty += dda.deltadisty;
            dda.mapy += dda.stepy;
            side = 1;
        }
        if (cub->map->map[dda.mapy][dda.mapx] == '1')
            hit = 1;
    }
    hitwall(&dda, side, &ray);
    ray.rayx = dda.rayx;
    ray.rayy = dda.rayy;
    return (ray);
}
