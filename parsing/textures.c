#include "../cub3d.h"

static char *get_value(t_game *cub, int index, int skip)
{
    char *value;
    int j = skip;
    value = cub->file[index];
    while (ft_iswhitespace(value[j]))
        j++;
    value = ft_strdup(&value[j]);
    cub->file = ft_remove2(cub->file, index);
    return value;
}

void textures(t_game *cub)
{
    int i = 0;
    char *str;
    int j = 0;
    while (cub->file[i])
    {
        j = 0;
        str = cub->file[i];
        while (ft_iswhitespace(str[j]))
            j++;
        if (ft_strncmp(str, "NO", 2) == 0)
        {
            cub->map->no = get_value(cub, i, 2);
            continue;
        }
        else if (ft_strncmp(str, "SO", 2) == 0)
        {
            cub->map->so = get_value(cub, i, 2);
            continue;
        }
        else if (ft_strncmp(str, "WE", 2) == 0)
        {
            cub->map->we = get_value(cub, i, 2);
            continue;
        }
        else if (ft_strncmp(str, "EA", 2) == 0)
        {
            cub->map->ea = get_value(cub, i, 2);
            continue;
        }
        i++;
    }
}


