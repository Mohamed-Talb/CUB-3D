/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:02:38 by mtaleb            #+#    #+#             */
/*   Updated: 2025/10/24 11:02:40 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*result;
	t_list	*new;

	curr = lst;
	result = 0;
	while (curr != NULL)
	{
		new = ft_lstnew(f(curr->content));
		if (new == NULL)
		{
			ft_lstclear(&result, del);
			return ((NULL));
		}
		ft_lstadd_back(&result, new);
		curr = curr->next;
	}
	return ((result));
}
