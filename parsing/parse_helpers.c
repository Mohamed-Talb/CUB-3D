#include "../cub3d.h"

char *get_trimed(int fd)
{
    char *line;
    char *result;

    line = get_next_line(fd);
    result = ft_strtrim(line, " \n");
    ft_free(line);
    return (result);
}

char *ft_substr_space(char **s)
{
    char *start;

    start = *s;
    while (**s && !ft_iswhitespace(**s))
        (*s)++;
    if (*s == start)
        return (NULL);
    return (ft_substr(start, 0, *s - start));
}

t_list *tokenize(char *str, char *(*rule)(char **))
{
    t_list *head;
    char *text;

    head = NULL;
    while (*str)
    {
        text = rule(&str);
        if (text == NULL)
            str++;
        else
            ft_lstadd_back(&head, ft_lstnew(text));
    }
    return (head);
}

void initeyes(t_game *cub)
{
    char pl;
    int  px;
    int  py;

    px = cub->map->px;
    py = cub->map->py;
    pl = cub->map->map[py][px];
    if (pl == 'N')
        cub->player->viewangle = -90;   // Facing North
    else if (pl == 'S')
        cub->player->viewangle = 90;  // Facing South
    else if (pl == 'E')
        cub->player->viewangle = 0;    // Facing East
    else if (pl == 'W')
        cub->player->viewangle = 180;  // Facing West
    cub->map->map[py][px] = '0';
}
