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

# include "./minilibx-linux/mlx.h"
#define M_PI 3.14159265358979323846
# define WIDTH 800
# define HEIGHT 480
# define ESC			65307
# define XK_LEFT		65361
# define XK_UP			65362
# define XK_RIGHT		65363
# define XK_DOWN		65364

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

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		wdt;
	int		hgt;
}				t_img;

typedef struct s_game
{
    t_map   *map;
    t_img   screen;
    char    **file;
    void	*mlx;
	void	*win;
    double     player_x;
    double     player_y;
    double     fov;
    double     step;
    double     view_angle;
    int     number_of_rays;
    int     draw_frame;
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
t_ray dda(t_map *map, double theta, double posx, double posy);
#endif