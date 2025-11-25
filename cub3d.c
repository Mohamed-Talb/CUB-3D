/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:58:00 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/15 14:31:55 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*getmemory(void)
{
	t_game	*cub;

	cub = ft_calloc(1, sizeof(t_game));
	cub->map = ft_calloc(1, sizeof(t_map));
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->textures = ft_calloc(1, sizeof(t_textures));
	return (cub);
}

int	main(int ac, char **av)
{
	t_game	*cub;
	char	*dot;

	if (ac != 2)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	dot = ft_strrchr(av[1], '.');
	if (!dot || dot == av[1] || *(dot - 1) == '/'
		|| ft_strcmp(dot, ".cub") != 0)
		errors("Error\nInvalid map extension Expected '.cub'\n", 1);
	cub = getmemory();
	parser(cub, av[1]);
	initgame(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	mlx_hook(cub->win, 2, 1L << 0, set_key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, set_key_release, cub);
	mlx_hook(cub->win, 17, 1L << 17, quit, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	mlx_loop(cub->mlx);
}
