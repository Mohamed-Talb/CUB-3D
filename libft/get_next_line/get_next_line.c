/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:35:38 by kel-mous          #+#    #+#             */
/*   Updated: 2024/12/21 19:42:54 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	ft_findchar(char *str, char to_find, int *len)
{
	*len = 0;
	while (str[*len])
	{
		if (str[(*len)++] == to_find)
		{
			return (*len);
		}
	}
	return (-1);
}

char	*ft_split_gnl(char **str, int position)
{
	char	*result;
	char	*remaining;
	int		len;

	len = ft_strlen(*str);
	result = ft_substr(*str, 0, position);
	if (result == NULL)
		return (NULL);
	remaining = ft_substr(*str, position, len - position);
	if (remaining == NULL)
	{
		ft_free(result);
		return (NULL);
	}
	ft_free(*str);
	*str = remaining;
	return (result);
}

char	*compute(char **str, int fd)
{
	int		len;
	char	*buff;

	while (1)
	{
		if (*str && ft_findchar(*str, '\n', &len) > -1)
		{
			return (ft_split_gnl(str, len));
		}
		buff = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
		if (read(fd, buff, BUFFER_SIZE) < 1)
		{
			ft_free(buff);
			if (*str && (*str)[0] != 0)
			{
				buff = *str;
				*str = NULL;
				return (buff);
			}
			return (NULL);
		}
		*str = ft_strjoin_es(*str, buff, 3);
		if (!(*str))
			return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*str;

	if (fd < 0 || fd > 1024)
		return (NULL);
	str = compute(&result, fd);
	if (str == 0)
	{
		if (result != NULL)
		{
			ft_free(result);
			result = NULL;
		}
		return (NULL);
	}
	return (str);
}
