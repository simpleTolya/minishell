/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:40:15 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 18:43:06 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	**last;

	if (!f)
		return (NULL);
	new_lst = 0;
	last = &new_lst;
	while (lst)
	{
		*last = ft_lstnew(f(lst->content));
		if (!(*last))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		last = &((*last)->next);
		lst = lst->next;
	}
	return (new_lst);
}
