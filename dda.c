/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:45:24 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 09:53:30 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initdda(t_dda *dda)
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

static void	distance(t_dda *dda, int side, t_ray *ray)
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

static void	hitwall(t_game *cub, t_dda *dda, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->sidedistx < dda->sidedisty)
		{
			dda->sidedistx += dda->deltadistx;
			dda->mapx += dda->stepx;
			ray->side = 0;
		}
		else
		{
			dda->sidedisty += dda->deltadisty;
			dda->mapy += dda->stepy;
			ray->side = 1;
		}
		if (cub->map->map[dda->mapy][dda->mapx] == '1')
			hit = 1;
	}
}

t_ray	dda(t_game *cub, double ray_dir_x, double ray_dir_y)
{
	t_dda	dda;
	t_ray	ray;

	dda.posx = cub->map->px;
	dda.posy = cub->map->py;
	dda.rayx = ray_dir_x;
	dda.rayy = ray_dir_y;
	ray.side = 0;
	initdda(&dda);
	hitwall(cub, &dda, &ray);
	distance(&dda, ray.side, &ray);
	ray.rayx = dda.rayx;
	ray.rayy = dda.rayy;
	return (ray);
}
