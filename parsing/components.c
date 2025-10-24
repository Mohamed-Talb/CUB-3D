/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:33:27 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 09:37:04 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_color(t_list *values)
{
	char	*colors;
	char	**parts;
	long	rgb[3];
	int		i;

	colors = NULL;
	while (values)
	{
		colors = ft_strjoin_es(colors, values->content, 1);
		values = values->next;
	}
	parts = ft_split(colors, ',');
	i = 0;
	while (parts[i] && i < 3)
	{
		rgb[i] = ft_atoy(parts[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			break ;
		i++;
	}
	if (i != 3)
		errors("Error\ninvalid rgb syntax\n", 1);
	ft_freedouble(parts);
	return (create_trgb(255, rgb[0], rgb[1], rgb[2]));
}

static int	is_textr(char *elemt)
{
	return (!ft_strcmp("NO", elemt) || !ft_strcmp("SO", elemt)
		|| !ft_strcmp("WE", elemt) || !ft_strcmp("EA", elemt));
}

static void	process_component(t_compnts *compnts, char *elemt, t_list *values)
{
	int	is_color;
	int	is_vsize;

	is_color = (!ft_strcmp("C", elemt) || !ft_strcmp("F", elemt));
	is_vsize = ft_lstsize(values) == 1;
	if ((!is_textr(elemt) && !is_color) || (is_textr(elemt) && !is_vsize))
		errors("Error\ninvalid component\n", 1);
	else if (!ft_strcmp("NO", elemt) && !compnts->path_no)
		compnts->path_no = ft_strdup(values->content);
	else if (!ft_strcmp("SO", elemt) && !compnts->path_so)
		compnts->path_so = ft_strdup(values->content);
	else if (!ft_strcmp("WE", elemt) && !compnts->path_we)
		compnts->path_we = ft_strdup(values->content);
	else if (!ft_strcmp("EA", elemt) && !compnts->path_ea)
		compnts->path_ea = ft_strdup(values->content);
	else if (!ft_strcmp("C", elemt) && !compnts->ceili)
		compnts->ceili = get_color(values);
	else if (!ft_strcmp("F", elemt) && !compnts->floor)
		compnts->floor = get_color(values);
	else
		errors("Error\nduplicated component\n", 1);
}

void	components(t_game *cub)
{
	t_list	*curr;
	char	*line;
	int		found;

	found = 0;
	line = get_trimed(cub->file_fd);
	while (found < 6 && line)
	{
		curr = tokenize(line, ft_substr_space);
		if (curr)
		{
			process_component(&cub->compnts, curr->content, curr->next);
			ft_lstclear(&curr, del);
			found++;
		}
		ft_free(line);
		line = get_trimed(cub->file_fd);
	}
}
