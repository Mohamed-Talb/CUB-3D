/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:02:03 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 11:02:05 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (lst == NULL)
		return (NULL);
	if (*lst == NULL)
	{
		*lst = new;
		return (NULL);
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
	return (*lst);
}
