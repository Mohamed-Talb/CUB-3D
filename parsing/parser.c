#include "../cub3d.h"

int get_color_n(t_list *values)
{
    char *colors;
    char **parts;
    int rgb[3];
    int i;

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
        rgb[i] = ft_atoi(parts[i]); // needs checking
        i++;
    }
    if (i != 3)
        errors("Error\ninvalid rgb syntax\n", 1);
    ft_freedouble(parts);
    return (create_trgb(255, rgb[0], rgb[1], rgb[2]));
}

void process_component(t_compnts *compnts, char *elemt, t_list *values)
{
    int is_textr;
    int is_color;
    int is_vsize;

    is_textr = !ft_strcmp("NO", elemt) || !ft_strcmp("SO", elemt)
        || !ft_strcmp("WE", elemt) || !ft_strcmp("EA", elemt);
    is_color = !ft_strcmp("C", elemt) || !ft_strcmp("F", elemt);
    is_vsize = ft_lstsize(values) == 1;
    if ((!is_textr && !is_color) || (is_textr && !is_vsize))
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
        compnts->ceili = get_color_n(values);
    else if (!ft_strcmp("F", elemt) && !compnts->floor)
        compnts->floor = get_color_n(values);
    else
        errors("Error\nduplicated component\n", 1);
}

void components(t_game *cub)
{
    t_list *curr;
    char *line;
    int found;

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

void parse_map(t_game *cub)
{
    char *line;

    line = get_trimed(cub->file_fd);
    while (!ft_strcmp(line, ""))
    {
        ft_free(line);
        line = get_trimed(cub->file_fd);
    }
    while (line && ft_strcmp(line, ""))
    {
        cub->map->map = ft_append2(cub->map->map, line);
        line = get_trimed(cub->file_fd);
    }
    while (!ft_strcmp(line, ""))
    {
        ft_free(line);
        line = get_trimed(cub->file_fd);
    }
    if (line)
        errors("Errors\nempty lines in map\n", 1);
}

void parser(t_game *cub, char *file)
{
    cub->file_fd = open(file, O_RDONLY);
	if (cub->file_fd == -1)
		errors(strerror(errno), 1);
    components(cub);
    parse_map(cub);
    cub->map->m_height = ft_strlen2(cub->map->map);
    mapvalidation(cub->map);
    checkwalls(cub->map);
    initeyes(cub);
}
