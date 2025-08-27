#include "../cub3d.h"

static char *get_value(t_game *cub, int index, int skip)
{
    char *value;

    value = ft_strdup(cub->file[index] + skip);
    cub->file = ft_remove2(cub->file, index);
    return value;
}

void textures(t_game *cub)
{
    int i = 0;
    while (cub->file[i])
    {
        if (ft_strncmp(cub->file[i], "NO", 2) == 0)
        {
            cub->map->no = get_value(cub, i, 2);
            continue;
        }
        else if (ft_strncmp(cub->file[i], "SO", 2) == 0)
        {
            cub->map->so = get_value(cub, i, 2);
            continue;
        }
        else if (ft_strncmp(cub->file[i], "WE", 2) == 0)
        {
            cub->map->we = get_value(cub, i, 2);
            continue;
        }
        else if (ft_strncmp(cub->file[i], "EA", 2) == 0)
        {
            cub->map->ea = get_value(cub, i, 2);
            continue;
        }
        i++;
    }
}


