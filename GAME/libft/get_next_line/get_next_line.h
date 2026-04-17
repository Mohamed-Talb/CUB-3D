/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:48:32 by kel-mous          #+#    #+#             */
/*   Updated: 2024/12/21 19:50:16 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*compute(char **str, int fd);
char	*ft_split_gnl(char **str, int position);
size_t	ft_strlen(const char *s);
void	ft_free(void *ptr);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_findchar(char *str, char to_find, int *len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin_es(char *str, char *buff, int choice);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
