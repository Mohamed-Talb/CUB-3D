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

void initdda(t_dda *dda, t_map *map, double theta)
{
    dda->rayx = cos(theta);
    dda->rayy = sin(theta);
    dda->mapx = (int)map->px; 
    dda->mapy = (int)map->py;
    dda->deltadistx = fabs(1 / dda->rayx); 
    dda->deltadisty = fabs(1 / dda->rayy);
    if (dda->rayx < 0)
    {
        dda->stepx = -1;
        dda->sidedistx = (map->px - dda->mapx) * dda->deltadistx;
    }
    else
    {
        dda->stepx = 1;
        dda->sidedistx = (dda->mapx + 1.0 - map->px) * dda->deltadistx;
    }
    if (dda->rayy < 0)
    {
        dda->stepy = -1;
        dda->sidedisty = (map->py - dda->mapy) * dda->deltadisty;
    }
    else
    {
        dda->stepy = 1;
        dda->sidedisty = (dda->mapy + 1.0 - map->py) * dda->deltadisty;
    }
}


t_ray *hitwall(t_dda *dda, t_map *map, int side, t_ray *ray)
{
    double walldist;
    double hitx;
    double hity;

    if (side == 0)
        walldist = dda->sidedistx - dda->deltadistx;
    else
        walldist = dda->sidedisty - dda->deltadisty;
    if (side == 0)
    {
        hitx = dda->mapx;
        if (dda->stepx < 0)
            hitx += 1.0;
        hity = map->py + walldist * dda->rayy;
    }
    else
    {
        hitx = map->px + walldist * dda->rayx;
        hity = dda->mapy;
        if (dda->stepy < 0)
            hity += 1.0;
    }
    ray->distance = walldist;
    ray->cor[0] = hitx;             
    ray->cor[1] = hity;             
    ray->side = side;
    return ray;
}


t_ray *dda(t_map *map, double theta)
{
    int hit = 0;
    int side;
    theta = theta * M_PI / 180.0;
    t_dda *dda = malloc(sizeof(t_dda));
    t_ray *ray = malloc(sizeof(t_ray));
    initdda(dda, map, theta);
    while (hit == 0)
    {
        if (dda->sidedistx < dda->sidedisty)
        {
            dda->sidedistx += dda->deltadistx;
            dda->mapx += dda->stepx;
            side = 0;
        }
        else
        {
            dda->sidedisty += dda->deltadisty;
            dda->mapy += dda->stepy;
            side = 1;
        }
        if (map->map[dda->mapy][dda->mapx] > 0)
            hit = 1;
    }
    hitwall(dda, map, side, ray);
    printf("Ray hit wall at map cell (%d,%d)\n", dda->mapx, dda->mapy);
    printf("Perpendicular distance to wall: %f\n", ray->distance);
    printf("Exact hit coordinates on wall: (%f, %f)\n", ray->cor[0], ray->cor[1]);
    return ray;
}
