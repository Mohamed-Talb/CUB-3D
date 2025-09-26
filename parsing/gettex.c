#include "../cub3d.h"

static char *get_value(char *str)
{
    str += 2;
    while (ft_iswhitespace(*str) && *str)
        str++;
    return (str);
}

void get_textures(t_game *cub, char *line, int tex)
{
    char *texname;
    
    texname = get_value(line);
    if (tex == 0)
    {
        cub->textures->wall_no.img = mlx_xpm_file_to_image(cub->mlx, texname,
                            &cub->textures->wall_no.wdt,
                            &cub->textures->wall_no.hgt);
    }
    else if (tex == 1)
    {
        cub->textures->wall_so.img = mlx_xpm_file_to_image(cub->mlx, texname,
                            &cub->textures->wall_so.wdt,
                            &cub->textures->wall_so.hgt);
    }
    else if (tex == 2)
    {
        cub->textures->wall_we.img = mlx_xpm_file_to_image(cub->mlx, texname,
                            &cub->textures->wall_we.wdt,
                            &cub->textures->wall_we.hgt);
    }   
    else if (tex == 3)
    {
        cub->textures->wall_ea.img = mlx_xpm_file_to_image(cub->mlx, texname,
                            &cub->textures->wall_ea.wdt,
                            &cub->textures->wall_ea.hgt);
    }
    if ((tex == 0 && !cub->textures->wall_no.img) || (tex == 1 && !cub->textures->wall_so.img) 
        || (tex == 2 && !cub->textures->wall_we.img) || (tex == 3 && !cub->textures->wall_ea.img))
    {
        printf("Failed to load texture: %s\n", texname);
        // free(texname);
        exit(1);
    }
}
