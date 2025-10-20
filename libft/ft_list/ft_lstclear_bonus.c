/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstclear_bonus.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kel-mous <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/04 17:35:55 by kel-mous		  #+#	#+#			 */
/*   Updated: 2024/11/04 17:49:44 by kel-mous		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */
#include "../libft.h"

void del(void *content)
{
    ft_free(content);
}

void del_skip(void *content)
{
	(void) content;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*temp;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		del(temp->content);
		ft_free(temp);
	}
	*lst = NULL;
}
