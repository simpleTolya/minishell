/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:31:24 by marmand           #+#    #+#             */
/*   Updated: 2022/01/23 12:42:28 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*tmp;

	if (!*lst)
		return (0);
	tmp = *lst;
	*lst = (*lst)->next;
	tmp->next = 0;
	return (tmp);
}
