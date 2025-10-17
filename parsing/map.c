#include "../cub3d.h"

int emptyline(char *line)
{
    while (*line && ft_iswhitespace(*line))
        line++;
    if(*line == 0)
        return 1;
    return 0;
}

// map doesn't support spaces in the middle
void parsemap(t_game *cub)
{
    int i = 0;

    while (emptyline(cub->file[i]))
        i++;
    cub->map->map = ft_strdup2(&cub->file[i]);
    if(cub->map->map == NULL)
        errors("Error: map doesnt exist\n", 1);
}
