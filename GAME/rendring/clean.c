/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:50:32 by kel-mous          #+#    #+#             */
/*   Updated: 2025/11/26 13:53:20 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	destroy(t_game *cub)
{
	if (cub->textures->wall_no.img)
		mlx_destroy_image(cub->mlx, cub->textures->wall_no.img);
	if (cub->textures->wall_so.img)
		mlx_destroy_image(cub->mlx, cub->textures->wall_so.img);
	if (cub->textures->wall_we.img)
		mlx_destroy_image(cub->mlx, cub->textures->wall_we.img);
	if (cub->textures->wall_ea.img)
		mlx_destroy_image(cub->mlx, cub->textures->wall_ea.img);
	if (cub->screen.img)
		mlx_destroy_image(cub->mlx, cub->screen.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	free_all_adresses();
	return (0);
}

int	quit(t_game *cub)
{
	destroy(cub);
	exit(0);
}

void	errors_destroy(t_game *cub, char *error, int exit_code)
{
	destroy(cub);
	ft_putstr_fd(error, 2);
	exit(exit_code);
}

void	errors(char *error, int exitcode)
{
	free_all_adresses();
	ft_putstr_fd(error, 2);
	exit(exitcode);
}
