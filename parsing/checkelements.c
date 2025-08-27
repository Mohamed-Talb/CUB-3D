#include "../cub3d.h"

void	checkelements(t_map *map)
{
	char	c;
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
			c = map->map[i][j];
			if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
            {
				// map->map[i][j] = 0;
                map->px = j + 0.5; 
                map->py = i + 0.5; 
                start += 1;
            }
			else if (c != '0' && c != '1' && c != 'S' && c != 'E' && c != 'W' && c != 'N' && c != ' ')
				displayerrors("Error\ninvalid element\n", 1);
			j++;
		}
		i++;
	}
	if (start != 1)
		displayerrors("Error\ninvalide elements\n", 1);
}
