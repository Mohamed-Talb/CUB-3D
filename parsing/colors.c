#include "../cub3d.h"



static char *get_value(t_game *cub, char *str)
{
    (void)cub;
    str += 1;
    while (*str && ft_iswhitespace(*str))
        str++;
    if (*str == '\0' || ft_isdigit(*str) == 0)
    {
        printf("Error: missing value after identifier\n"); // wrong err msg should be Error\n followed by something
            //error
        exit(1);
    }
    return (str);
}

// function to be optimized
// btw something like: C 38, 140, 4294967476 overflows and goes undetected
int *get_color(t_game *cub, char *str, int color)
{
    // check chars
    // CHECK F5, 5,5   AND F/  5, 5,5

    int     *rgb;
    char    **parts;
    int      i;

    str = get_value(cub, str);
    rgb = ft_malloc(sizeof(int) * 3);
    if (!rgb)
    {
        printf("Error: malloc failed for rgb\n");
        exit(1);
            //error
    }
    parts = ft_split(str, ',');
    if (!parts)
    {
        free(rgb);
        printf("Error: failed to split color string: %s\n", str);
        //error
        exit(1);
    }
    i = 0;
    while (i < 3 && parts[i])
    {
        rgb[i] = ft_atoi(parts[i]);
        if (rgb[i] < 0 || rgb[i] > 255)
        {
            printf("Error: invalid RGB value (%d), must be 0–255\n", rgb[i]);
            //error
            exit(1);
        }
        i++;
    }
    if (i != 3 || parts[i] != NULL)
    {
        printf("Error: color must have exactly 3 values (got %d)\n", i);
        //error
        exit(1);
    }
    if (color == C)
        cub->map->cieling = create_trgb(0, rgb[0], rgb[1], rgb[2]);
    else if (color == F)
        cub->map->floor = create_trgb(0, rgb[0], rgb[1], rgb[2]);
    ft_freedouble(parts);
    return (rgb);
}
