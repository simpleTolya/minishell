/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_star.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:25:37 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:52:24 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

static int	ft_is_match_pattern(const char *str, const char *pattern)
{
	int			word_strt_i;
	int			i;
	const char	**words = (const char **) ft_split(pattern, '*');
	t_string	copy;

	word_strt_i = 0;
	ft_str_init(&copy, str);
	i = 0;
	while (words[i])
	{
		word_strt_i = ft_str_c_find(&copy, words[i]);
		if ((i == 0 && pattern[0] != '*' && word_strt_i != 0) || (word_strt_i
				== -1) || (copy.c_str[word_strt_i + ft_strlen(words[i])] != 0
				&& !words[i + 1] && pattern[ft_strlen(pattern) - 1] != '*'))
		{
			ft_str_clear(&copy);
			ft_clear_split_strs((char **)words);
			return (0);
		}
		ft_str_erase(&copy, 0, word_strt_i + ft_strlen(words[i++]));
	}
	ft_str_clear(&copy);
	ft_clear_split_strs((char **)words);
	return (1);
}

static void	ft_pass(void *nothing)
{
	(void) nothing;
}

static void	ft_nadia(t_list **lst, char *pattern)
{
	DIR				*dir_file;
	struct dirent	*file;
	const char		*pwd = getcwd(0, 0);
	int				flag;

	dir_file = opendir(pwd);
	free((void *) pwd);
	file = readdir(dir_file);
	flag = 1;
	while (file)
	{
		if (file->d_name[0] != '.' && pattern[0]
			&& ft_is_match_pattern(file->d_name, pattern))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(file->d_name)));
			flag = 0;
		}
		file = readdir(dir_file);
	}
	closedir(dir_file);
	if (flag)
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(pattern)));
}

void	ft_paste_wildcard_star(t_process_block *p_block, t_utils *util)
{
	t_list	*n_argv;
	t_list	*tmp;
	int		i;

	(void) util;
	n_argv = 0;
	i = 0;
	while (p_block->argv[i])
		ft_nadia(&n_argv, p_block->argv[i++]);
	ft_clear_split_strs(p_block->argv);
	p_block->argv = malloc(sizeof(char *) * (ft_lstsize(n_argv) + 1));
	i = 0;
	tmp = n_argv;
	while (n_argv)
	{
		p_block->argv[i++] = n_argv->content;
		n_argv = n_argv->next;
	}
	p_block->argv[i] = 0;
	ft_lstclear(&tmp, ft_pass);
}
