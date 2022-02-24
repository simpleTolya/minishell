/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:34:21 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 19:02:26 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_del;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		to_del = *lst;
		*lst = (*lst)->next;
		del(to_del->content);
		free(to_del);
	}
}
