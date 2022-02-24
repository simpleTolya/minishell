/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_procblock.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:03:28 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:43:13 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

int	ft_transform_words_to_procblock(t_process_block *p_block, t_list **words,
	t_utils *util)
{
	if (ft_notcorrect_procblock(words))
		return (1);
	ft_replace_magic_lst(words, util);
	ft_str_init(&p_block->_path, "");
	ft_get_redirects(p_block, words);
	ft_get_arguments(p_block, words);
	ft_change_home_dir(p_block, util);
	ft_paste_wildcard_star(p_block, util);
	if (ft_get_path_to_process(*p_block->argv,
			(const char **)util->env, &p_block->_path))
		ft_str_c_copy(&p_block->_path, *p_block->argv);
	p_block->_fd_input = -1;
	p_block->_fd_output = -1;
	return (0);
}

static int	ft_get_files_count(t_list *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		if (ft_is_redir_sym(tmp->content))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_get_redirects(t_process_block *block, t_list **words)
{
	t_file_info		*file_info;
	int				flag;
	int				i;

	block->files_count = ft_get_files_count(*words);
	file_info = malloc(block->files_count * sizeof(t_file_info));
	i = 0;
	while ((*words) && i < block->files_count)
	{
		flag = ft_is_redir_sym((*words)->content);
		if (flag)
		{
			ft_str_init(&file_info[i].file_name, "");
			ft_str_copy(&file_info[i].file_name, (*words)->next->content);
			file_info[i].file_flag = flag;
			words = &((*words)->next);
			if (++i == block->files_count)
				break ;
		}
		words = &((*words)->next);
	}
	block->files = file_info;
}
