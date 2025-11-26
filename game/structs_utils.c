/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:23:52 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/26 13:56:40 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_addr(t_game *cub)
{
	cub->textures->wall_ea.addr = mlx_get_data_addr(cub->textures->wall_ea.img,
			&cub->textures->wall_ea.bits_per_pixel,
			&cub->textures->wall_ea.line_length,
			&cub->textures->wall_ea.endian);
	cub->textures->wall_we.addr = mlx_get_data_addr(cub->textures->wall_we.img,
			&cub->textures->wall_we.bits_per_pixel,
			&cub->textures->wall_we.line_length,
			&cub->textures->wall_we.endian);
	cub->textures->wall_no.addr = mlx_get_data_addr(cub->textures->wall_no.img,
			&cub->textures->wall_no.bits_per_pixel,
			&cub->textures->wall_no.line_length,
			&cub->textures->wall_no.endian);
	cub->textures->wall_so.addr = mlx_get_data_addr(cub->textures->wall_so.img,
			&cub->textures->wall_so.bits_per_pixel,
			&cub->textures->wall_so.line_length,
			&cub->textures->wall_so.endian);
	return (cub->textures->wall_ea.addr && cub->textures->wall_we.addr
		&& cub->textures->wall_no.addr && cub->textures->wall_so.addr);
}

void	initscreen(t_game *cub)
{
	cub->screen.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->screen.img)
		errors_destroy(cub, "Failed to load screen\n", 1);
	cub->screen.addr = mlx_get_data_addr(cub->screen.img,
			&cub->screen.bits_per_pixel, &cub->screen.line_length,
			&cub->screen.endian);
	if (!cub->screen.addr)
		errors_destroy(cub, "Failed to load screen\n", 1);
}

void	init_textures(t_game *cub)
{
	cub->textures->wall_no.img = mlx_xpm_file_to_image(cub->mlx,
			cub->compnts.path_no, &cub->textures->wall_no.wdt,
			&cub->textures->wall_no.hgt);
	cub->textures->wall_so.img = mlx_xpm_file_to_image(cub->mlx,
			cub->compnts.path_so, &cub->textures->wall_so.wdt,
			&cub->textures->wall_so.hgt);
	cub->textures->wall_we.img = mlx_xpm_file_to_image(cub->mlx,
			cub->compnts.path_we, &cub->textures->wall_we.wdt,
			&cub->textures->wall_we.hgt);
	cub->textures->wall_ea.img = mlx_xpm_file_to_image(cub->mlx,
			cub->compnts.path_ea, &cub->textures->wall_ea.wdt,
			&cub->textures->wall_ea.hgt);
	if (!(cub->textures->wall_no.img) || !(cub->textures->wall_so.img)
		|| !(cub->textures->wall_we.img) || !(cub->textures->wall_ea.img)
		|| !init_addr(cub))
		errors_destroy(cub, "Failed to load screen\n", 1);
}

void	init_player(t_game *cub)
{
	cub->player->fov = 75;
	cub->player->turnperiod = 1.75;
	cub->player->traverseperiod = 8;
	cub->player->collisionmargin = 0.3;
	cub->player->plane = tan((cub->player->fov * M_PI / 180.0) / 2);
}

t_game	*initgame(t_game *cub)
{
	cub->nrays = WIDTH;
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		errors_destroy(cub, NULL, 1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	if (cub->win == NULL)
		errors_destroy(cub, NULL, 1);
	initscreen(cub);
	init_textures(cub);
	init_player(cub);
	gettimeofday(&cub->frame_interval, NULL);
	return (cub);
}
