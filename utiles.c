#include "cub3d.h"

void	displayerrors(char *error, int exitcode)
{
    // free_all_adresses();
	ft_putstr_fd(error, 2);
	exit(exitcode);
}