/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_magic_chars.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:13:31 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:52:57 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

void	ft_replace_magic_lst(t_list **lst, t_utils *util)
{
	const t_list	*tmp = *lst;

	while (tmp)
	{
		if (ft_strncmp(((t_string *)tmp->content)->c_str, "<<", 3) == 0)
			tmp = tmp->next;
		else
			ft_replace_magic(tmp->content, util);
		tmp = tmp->next;
	}
}

void	ft_replace_var_to_value(t_string *var, t_utils *util)
{
	int		i;
	char	*tmp;

	if (ft_strncmp(var->c_str, "?", 2) == 0)
	{
		tmp = ft_itoa(util->last_process_code);
		ft_str_c_copy(var, tmp);
		free(tmp);
		return ;
	}
	i = 0;
	ft_str_append(var, '=');
	while (util->env[i])
	{
		if (ft_strncmp(var->c_str, util->env[i], var->size) == 0)
		{
			ft_str_c_copy(var, util->env[i] + var->size);
			return ;
		}
		i++;
	}
	ft_str_c_copy(var, "");
}
