/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:24:38 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 10:25:16 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long	time_to_long(struct timeval timestamp)
{
	return (timestamp.tv_sec * 1000000 + timestamp.tv_usec);
}

double	get_timestamp(struct timeval current, struct timeval begining)
{
	return ((time_to_long(current) - time_to_long(begining)) / 1000000.0);
}

double	prtct_dnmtr(double value)
{
	if (value == 0)
		return (0.0000001);
	return (value);
}
