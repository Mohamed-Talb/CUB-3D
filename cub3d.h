#ifndef CUB3D_H
# define CUB3D_H

#include "structures.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <ctype.h>
# include <fcntl.h>
# include <math.h>

# include "mlx.h"
# define M_PI 3.14159265358979323846
# define WIDTH 800
# define HEIGHT 480
# define ESC			65307
# define XK_LEFT		65361
# define XK_UP			65362
# define XK_RIGHT		65363
# define XK_DOWN		65364

#define NO 0
#define SO 1
#define WE 2
#define EA 3
#define C  4
#define F  5

#define DEG_TO_RAD(angle) ((angle) * (M_PI / 180.0))
char    *get_next_line(int fd);

void	errors(char *error, int exitcode);


// PARSING
void    filecontent(t_game *cub, char *file);
void    parsemap(t_game *cub);
int     *get_color(t_game *cub, char *str, int color);
void    checkwalls(t_map *map);
void    parser(t_game *cub, char *file);
void    mapvalidation(t_map *map);
void    get_textures(t_game *cub, char *line, int tex);

t_game *initgame(t_game *cub);

t_ray   dda(t_game *cub, double ray_dir_x, double ray_dir_y);

int     destroy(t_game *cub);
int     render_frame(t_game *cub);
void    initaddr(t_game *cub);
void    components(t_game *cub);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int get_pixel_from_texture(t_img *img, int x, int y);
int	         create_trgb(int t, int r, int g, int b);
void         drawcolum(t_game *cub, int x, double dist, double wallX, t_ray *ray);
t_game      *initgame(t_game *cub);

double      get_timestamp(struct timeval current, struct timeval begining);
void        key_hook(t_game *cub, double frames_diff);
int         set_key_release(int keysym, t_game *cub);
int         set_key_press(int keysym, t_game *cub);
void collision(t_map *map, t_move move);

#endif