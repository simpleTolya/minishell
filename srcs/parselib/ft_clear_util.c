/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:55:38 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 10:59:39 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

void	ft_clear_split_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_clear_util(t_utils *util)
{
	ft_clear_split_strs(util->env);
}

void	ft_clear_pblock(void *p_block)
{
	int	i;

	ft_str_clear(&((t_process_block *)p_block)->_path);
	i = 0;
	while (((t_process_block *)p_block)->argv[i])
	{
		free(((t_process_block *)p_block)->argv[i]);
		i++;
	}
	free(((t_process_block *)p_block)->argv);
	i = 0;
	while (i < ((t_process_block *)p_block)->files_count)
	{
		ft_str_clear(&((t_process_block *)p_block)->files[i].file_name);
		i++;
	}
	free(((t_process_block *)p_block)->files);
}

void	ft_clear_string(void *str)
{
	ft_str_clear(str);
	free(str);
}
