#include "../cub3d.h"

static char *get_value(t_game *cub, int index, int skip)
{
    char *value;

    value = ft_strdup(cub->file[index] + skip);
    cub->file = ft_remove2(cub->file, index);
    return value;
}

static int *parse_rgb(const char *str)
{
    int *rgb;
    char **parts;
    int i;

    rgb = ft_malloc(sizeof(int) * 3);
    parts = ft_split(str, ',');
    if (!parts)
    {
        free(rgb);
        return NULL;
    }
    i = 0;
    while (i < 3 && parts[i])
    {
        rgb[i] = ft_atoi(parts[i]);
        i++;
    }
    ft_freedouble(parts);
    return rgb;
}

void colors(t_game *cub)
{
    int i = 0;

    while (cub->file[i])
    {
        if (ft_strncmp(cub->file[i], "F", 1) == 0)
        {
            char *val = get_value(cub, i, 1);
            cub->map->f = parse_rgb(val);
            free(val);
            continue;
        }
        else if (ft_strncmp(cub->file[i], "C", 1) == 0)
        {
            char *val = get_value(cub, i, 1);
            cub->map->c = parse_rgb(val);
            free(val);
            continue;
        }
        i++;
    }
}
