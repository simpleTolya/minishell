/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pobject_append_lexeme.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:25:37 by marmand           #+#    #+#             */
/*   Updated: 2022/01/21 17:33:26 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

int	ft_pobject_append_lexeme(t_parse_object *p_obj, const t_string *lexeme)
{
	t_string	*str;
	t_list		*node;

	if (lexeme->size == 0)
		return (0);
	str = malloc(sizeof(t_string));
	if (!str)
		return (1);
	if (ft_str_init(str, lexeme->c_str))
	{
		free(str);
		return (1);
	}
	node = ft_lstnew(str);
	if (!node)
	{
		ft_str_clear(str);
		free(str);
		return (1);
	}
	ft_lstadd_back(&p_obj->lexeme_lst, node);
	return (0);
}
