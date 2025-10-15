#include "../cub3d.h"

static char *get_value(char *str)
{
    str += 2;
    while (*str && ft_iswhitespace(*str))
        str++;
    return str;
}

void get_textures(t_game *cub, char *line, int tex)
{
    char *texname;

    texname = get_value(line);
    cub->map->tpaths[tex] = texname;
}
