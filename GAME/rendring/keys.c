/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:17:45 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 11:24:36 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_key_press(int keysym, t_game *cub)
{
	if (keysym == XK_W || keysym == XK_UP)
		cub->keys.up = true;
	else if (keysym == XK_S || keysym == XK_DOWN)
		cub->keys.down = true;
	else if (keysym == XK_A)
		cub->keys.left = true;
	else if (keysym == XK_D)
		cub->keys.right = true;
	else if (keysym == XK_LEFT)
		cub->keys.rot_left = true;
	else if (keysym == XK_RIGHT)
		cub->keys.rot_right = true;
	else if (keysym == ESC)
		(quit(cub));
	return (0);
}

int	set_key_release(int keysym, t_game *cub)
{
	if (keysym == XK_W || keysym == XK_UP)
		cub->keys.up = false;
	else if (keysym == XK_S || keysym == XK_DOWN)
		cub->keys.down = false;
	else if (keysym == XK_A)
		cub->keys.left = false;
	else if (keysym == XK_D)
		cub->keys.right = false;
	else if (keysym == XK_LEFT)
		cub->keys.rot_left = false;
	else if (keysym == XK_RIGHT)
		cub->keys.rot_right = false;
	return (0);
}
