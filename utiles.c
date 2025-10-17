#include "cub3d.h"

void	errors(char *error, int exitcode)
{
    // free_all_adresses(); // important
	ft_putstr_fd(error, 2);
	exit(exitcode);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int get_pixel_from_texture(t_img *img, int x, int y)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

long	time_to_long(struct timeval timestamp)
{
	return (timestamp.tv_sec * 1000000 + timestamp.tv_usec);
}

double	get_timestamp(struct timeval current, struct timeval begining)
{
	return ((time_to_long(current) - time_to_long(begining)) / 1000000.0);
}