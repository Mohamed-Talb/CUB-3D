/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:59:49 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 11:24:53 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/usr/include/minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "game/structures.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define M_PI 3.14159265358979323846
# define WIDTH 800
# define HEIGHT 480
# define ESC 65307

// Arrow keys
# define XK_LEFT 65361
# define XK_UP 65362
# define XK_RIGHT 65363
# define XK_DOWN 65364

// WASD keys
# define XK_W 119
# define XK_A 97
# define XK_S 115
# define XK_D 100

// Escape key
# define ESC 65307

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define C 4
# define F 5

char			*get_next_line(int fd);
void			errors(char *error, int exitcode);

// PARSING
char			*get_trimed(int fd);
void			initeyes(t_game *cub);
void			checkwalls(t_map *map);
void			components(t_game *cub);
void			mapvalidation(t_map *map);
char			*ft_substr_space(char **s);
void			parser(t_game *cub, char *file);
t_list			*tokenize(char *str, char *(*rule)(char **));

// INITIALIZATIONS
int				init_addr(t_game *cub);
t_game			*initgame(t_game *cub);

// RENDERING
int				render_frame(t_game *cub);
void			collision(t_map *map, t_move move);
int				set_key_press(int keysym, t_game *cub);
int				set_key_release(int keysym, t_game *cub);
void			key_hook(t_game *cub, double frames_diff);
t_ray			dda(t_game *cub, double ray_dir_x, double ray_dir_y);

// UTILES
double			prtct_dnmtr(double value);
int				create_trgb(int t, int r, int g, int b);
unsigned int	get_pixel_from_texture(t_img *img, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
double			get_timestamp(struct timeval current, struct timeval begining);
void			drawcolum(t_game *cub, int x, t_ray *ray);

// CLEANING
int				quit(t_game *cub);
int				destroy(t_game *cub);
void			errors_destroy(t_game *cub, char *error, int exit_code);

#endif