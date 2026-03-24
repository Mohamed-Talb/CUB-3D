/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:02:45 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 11:02:47 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	if (node == NULL)
		return ((NULL));
	node->content = content;
	node->next = NULL;
	return ((node));
}
