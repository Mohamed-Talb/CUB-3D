/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:33:27 by mtaleb            #+#    #+#             */
/*   Updated: 2025/11/26 17:02:42 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_occurence(char *str, char c)
{
	int	occurred;

	occurred = 0;
	while (*str)
	{
		if (*str == c)
			occurred++;
		str++;
	}
	return (occurred);
}

static int	get_color(char *line)
{
	char	*color;
	char	**parts;
	long	rgb[3];
	int		i;

	color = NULL;
	if (!in_set(WHITESPACES, *line))
		errors("Error\nInvalide Components\n", 1);
	parts = ft_split(line, ',');
	i = 0;
	while (parts[i] && i < 3)
	{
		color = ft_strtrim(parts[i], WHITESPACES);
		if (hasfrom_set(color, WHITESPACES))
			break ;
		rgb[i] = ft_atoy(color);
		ft_free(color);
		if (rgb[i] < 0 || rgb[i] > 255)
			break ;
		i++;
	}
	if (ft_strlen2(parts) != 3 || i != 3 || count_occurence(line, ',') != 2)
		errors("Error\ninvalid rgb syntax\n", 1);
	ft_freedouble(parts);
	return (create_trgb(255, rgb[0], rgb[1], rgb[2]));
}

static void	process_component(t_game *cub, char *line)
{
	if (!ft_strncmp("NO", line, 2) && !cub->compnts.path_no)
		cub->compnts.path_no = sidescheck(line + 2);
	else if (!ft_strncmp("SO", line, 2) && !cub->compnts.path_so)
		cub->compnts.path_so = sidescheck(line + 2);
	else if (!ft_strncmp("WE", line, 2) && !cub->compnts.path_we)
		cub->compnts.path_we = sidescheck(line + 2);
	else if (!ft_strncmp("EA", line, 2) && !cub->compnts.path_ea)
		cub->compnts.path_ea = sidescheck(line + 2);
	else if (!ft_strncmp("C", line, 1) && !cub->compnts.ceili)
		cub->compnts.ceili = get_color(line + 1);
	else if (!ft_strncmp("F", line, 1) && !cub->compnts.floor)
		cub->compnts.floor = get_color(line + 1);
	else
		errors("Error\ninvalid component\n", 1);
}

void	components(t_game *cub)
{
	char	*line;
	int		found;
	int		i;

	found = 0;
	line = get_trimed(cub->file_fd);
	while (found < 6 && line)
	{
		i = 0;
		while (in_set(WHITESPACES, line[i]))
			i++;
		if (line[i] == '\0')
		{
			ft_free(line);
			line = get_trimed(cub->file_fd);
			continue ;
		}
		process_component(cub, &line[i]);
		found++;
		ft_free(line);
		line = get_trimed(cub->file_fd);
	}
	if (found != 6)
		errors("Error\nInvalid components\n", 1);
}
