#ifndef CUB3D_H
# define CUB3D_H

#include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

typedef struct s_ray
{
    double distance;
    double cor[2];
    double side;
} t_ray;

typedef struct s_map
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char **map;
    int  m_height;
    int  m_width;
    int  px;
    int  py;
    int  *c;
    int  *f;
}   t_map;

typedef struct s_game
{
    t_map *map;
    char **file;
    
} t_game;

char    *get_next_line(int fd);

void	displayerrors(char *error, int exitcode);


// PARSING
void    filecontent(t_game *cub, char *file);
void    parsemap(t_game *cub);
void    textures(t_game *cub);
void    colors(t_game *cub);
void    checkwalls(t_map *map);
void    parser(t_game *cub, char *file);
void    checkelements(t_map *map);
// STRUCTES UTILES
void initgame(t_game **cub);


// DDA
t_ray *dda(t_map *map, double theta);
#endif