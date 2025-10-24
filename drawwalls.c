/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:17:09 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 10:17:10 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*select_texture(t_game *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayx > 0)
			return (&cub->textures->wall_we);
		else
			return (&cub->textures->wall_ea);
	}
	else
	{
		if (ray->rayy > 0)
			return (&cub->textures->wall_no);
		else
			return (&cub->textures->wall_so);
	}
}

static void	drawceiling(t_game *cub, int x, int starty)
{
	int	y;

	y = 0;
	while (y < starty)
	{
		my_mlx_pixel_put(&cub->screen, x, y, cub->compnts.ceili);
		y++;
	}
}

static void	drawfloor(t_game *cub, int x, int endy)
{
	int	y;

	y = endy + 1;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&cub->screen, x, y, cub->compnts.floor);
		y++;
	}
}

t_column	init_column(t_game *cub, double dist, double wallx, t_ray *ray)
{
	t_column	col;

	col.lineh = HEIGHT / dist;
	col.starty = (HEIGHT - col.lineh) / 2;
	if (col.starty < 0)
		col.starty = 0;
	col.endy = col.starty + col.lineh;
	if (col.endy >= HEIGHT)
		col.endy = HEIGHT - 1;
	wallx = wallx - floor(wallx);
	col.texture = select_texture(cub, ray);
	col.texx = wallx * col.texture->wdt;
	if (col.texx >= col.texture->wdt)
		col.texx = col.texture->wdt - 1;
	if (col.texx < 0)
		col.texx = 0;
	return (col);
}

void	drawcolum(t_game *cub, int x, t_ray *ray)
{
	t_column	col;
	int			y;
	int			texy;
	int			color;
	int			adstart;

	col = init_column(cub, ray->distance, ray->wallx, ray);
	y = col.starty;
	adstart = (HEIGHT - col.lineh) / 2;
	drawceiling(cub, x, col.starty);
	while (y <= col.endy)
	{
		texy = (y - adstart) * col.texture->hgt / col.lineh;
		if (texy >= col.texture->hgt)
			texy = col.texture->hgt - 1;
		if (texy < 0)
			texy = 0;
		color = get_pixel_from_texture(col.texture, col.texx, texy);
		my_mlx_pixel_put(&cub->screen, x, y, color);
		y++;
	}
	drawfloor(cub, x, col.endy);
}
