/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:05:59 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:06:02 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	r;
	int	i;

	i = 0;
	r = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + nptr[i] - '0';
		i++;
	}
	return (r * sign);
}

long	ft_atoy_get(const char *nptr, long result, int sign)
{
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (!nptr[0])
			return (MAX);
	}
	else if (!ft_isdigit(*nptr))
		return (MAX);
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - 48;
		if (result > MAX || (result == MAX && sign == 1))
			return (MAX);
		nptr++;
	}
	if (!((*nptr > 8 && *nptr < 14) || *nptr == 32 || *nptr == 0))
		return (MAX);
	return (((result * sign)));
}

long	ft_atoy(const char *nptr)
{
	return (ft_atoy_get(nptr, 0, 1));
}
