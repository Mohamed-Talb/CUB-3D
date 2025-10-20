#include "../cub3d.h"

static void checkelement(t_map *map, int i, int j, int *start)
{
	char elem;

	elem = map->map[i][j];
	if (elem == 'S' || elem == 'N' || elem == 'E' || elem == 'W')
	{
		map->px = j + 0.5;
		map->py = i + 0.5;
		*start += 1;
	}
	else if (elem != '0' && elem != '1' && elem != 'S' 
			&& elem != 'E' && elem != 'W'
			&& elem != 'N' && elem != ' ')
		errors("Error\ninvalid element\n", 1);
}

void	mapvalidation(t_map *map)
{
    int     i;
    int     j;
    int     start;

	start = 0;
    i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			checkelement(map, i, j, &start);
			j++;
		}
		i++;
	}
	if (start != 1)
		errors("Error\ninvalide elements\n", 1);
}

static char safe_get_char(t_map *map, int i, int j)
{
    if (i < 0 || i >= map->m_height)
        return ' ';
    if (j < 0 || j >= ft_strlen(map->map[i]))
        return ' ';
    return map->map[i][j];
}

static int find_space(t_map *map, int i, int j)
{
    char up;
    char down;
    char left;
    char right;

    up  = safe_get_char(map, i - 1, j);
    down = safe_get_char(map, i + 1, j);
    left = safe_get_char(map, i, j - 1);
    right = safe_get_char(map, i, j + 1);  
    if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
        return (1);
    return (0);
}

void checkwalls(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] != '1' && map->map[i][j] != ' ')
                if (find_space(map, i, j))
                    errors("Error\nMap is not enclosed by walls\n", 1);
            j++;
        }
        i++;
    }
}

