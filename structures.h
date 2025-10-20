#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <sys/time.h>
#include <stdbool.h>

typedef struct s_ray
{
    double distance;
    double side;
    double rayx;
    double rayy;
    double wallx;
} t_ray;

typedef struct s_draw
{
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    double  ray_dir_x;
    double  ray_dir_y;
    double  camera_x;
    t_ray   ray;
}   t_draw;

typedef struct s_dda
{
    double posx;
    double posy;
    double rayx;
    double rayy;
    double sidedisty;
    double sidedistx;
    double deltadisty;
    double deltadistx;
    int mapx;
    int mapy;
    int stepx;
    int stepy;
} t_dda;

typedef struct s_img 
{
    int		wdt;
    int		hgt;
    void	*img;
    char	*addr;
    int		endian;
    int		line_length;
    int		bits_per_pixel;
}				t_img;

typedef struct s_move
{
    double added_x;
    double added_y;
    int safe_px;
    int safe_py;
    int edge_decision;
} t_move;

typedef struct s_map
{
    double  py;
    double  px;
    int     floor;
    char    **map;
    int     m_width;
    int     cieling;
    int     m_height;
    char    **tpaths;
}   t_map;

typedef struct s_textures
{
	t_img wall_no;
	t_img wall_we;
	t_img wall_so;
	t_img wall_ea;
}	t_textures;

typedef struct s_keys
{
	bool up;
	bool down;
	bool left;
	bool right;
}	t_keys;

typedef struct s_player
{
    double  fov;
    double  plane;
    double  viewangle;
    double  turnperiod;
    double  traverseperiod;
    double  collisionmargin;
} t_player;

typedef struct s_compnts
{
	char *path_no;
	char *path_we;
	char *path_so;
	char *path_ea;
    int     floor;
    int     ceili;
}	t_compnts;

typedef struct s_game
{
    t_map       *map;
    t_keys      keys;
    void        *mlx;
	void        *win;
    int         nrays;
    t_img       screen;
    char        **file;
    t_player    *player;
    t_compnts   compnts;
    int         file_fd;
    int         drawframe;
	t_textures  *textures;
    struct timeval  frame_interval;
} t_game;

#endif
