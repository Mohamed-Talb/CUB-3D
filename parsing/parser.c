/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:33:08 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/14 11:03:07 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_map(t_game *cub)
{
	char	*line;

	line = get_trimed(cub->file_fd);
	while (line && respects_set(line, " "))
	{
		ft_free(line);
		line = get_trimed(cub->file_fd);
	}
	while (line && !respects_set(line, " "))
	{
		cub->map->map = ft_append2(cub->map->map, line);
		line = get_trimed(cub->file_fd);
	}
	while (line && respects_set(line, " "))
	{
		ft_free(line);
		line = get_trimed(cub->file_fd);
	}
	if (line || !cub->map->map)
		errors("Errors\nInvalid map\n", 1);
}

void	parser(t_game *cub, char *file)
{
	cub->file_fd = open(file, O_RDONLY);
	if (cub->file_fd == -1)
		errors(strerror(errno), 1);
	components(cub);
	parse_map(cub);
	mapvalidation(cub->map);
	initeyes(cub);
}
