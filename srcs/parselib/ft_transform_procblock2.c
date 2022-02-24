/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_procblock2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:32:18 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 13:10:55 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

void	ft_change_home_dir(t_process_block *p_block, t_utils *util)
{
	int			i;
	t_string	home_dir;
	int			flag;

	ft_str_init(&home_dir, 0);
	flag = ft_get_var_value("HOME", util, &home_dir);
	i = 0;
	while (p_block->argv[i])
	{
		if (p_block->argv[i][0] == '~')
		{
			if (flag)
			{
				ft_str_clear(&home_dir);
				ft_print_parse_error(HOME_NOT_SET_ERROR);
				return ;
			}
			ft_str_c_paste(&home_dir, p_block->argv[i] + 1, -1);
			free(p_block->argv[i]);
			p_block->argv[i] = ft_strdup(home_dir.c_str);
		}
		i++;
	}
	ft_str_clear(&home_dir);
}

static int	ft_check_redir_error(t_string *str)
{
	if (ft_strncmp(str->c_str, ">>", 3) == 0)
		return (ft_print_parse_error(UNEXPECTED_GRTGRT_ERROR));
	if (ft_strncmp(str->c_str, "<<", 3) == 0)
		return (ft_print_parse_error(UNEXPECTED_LSSLSS_ERROR));
	if (ft_strncmp(str->c_str, ">", 2) == 0)
		return (ft_print_parse_error(UNEXPECTED_GRT_ERROR));
	if (ft_strncmp(str->c_str, "<", 2) == 0)
		return (ft_print_parse_error(UNEXPECTED_LSS_ERROR));
	return (0);
}

int	ft_notcorrect_procblock(t_list **words)
{
	const t_list	*tmp = *words;

	while (tmp)
	{
		if (ft_strncmp(((t_string *)tmp->content)->c_str, ";", 2) == 0
			|| ft_strncmp(((t_string *)tmp->content)->c_str, "\\", 2) == 0
			|| ft_strncmp(((t_string *)tmp->content)->c_str, "&", 2) == 0)
			return (ft_print_parse_error(UNSUPPORTED_TOKEN_ERROR));
		if (ft_is_redir_sym(tmp->content))
		{
			if (tmp->next)
			{
				if (ft_strncmp(((t_string *)tmp->next->content)->c_str,
						"*", 2) == 0)
					return (ft_print_parse_error(AMBIGUOUS_REDIRECT_ERROR));
				if (ft_check_redir_error(tmp->next->content))
					return (1);
			}
			else
				return (ft_print_parse_error(UNEXPECTED_NEWLINE_ERROR));
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_get_arguments(t_process_block *p_block, t_list **words)
{
	int	i;
	int	argc;

	argc = ft_lstsize(*words) - (p_block->files_count * 2);
	p_block->argv = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (i < argc)
	{
		if (ft_is_redir_sym((*words)->content))
			words = &((*words)->next);
		else
			p_block->argv[i++] = ft_strdup(((t_string *)
						(*words)->content)->c_str);
		words = &((*words)->next);
	}
	p_block->argv[i] = 0;
}

int	ft_is_redir_sym(t_string *str)
{
	if (ft_strncmp(str->c_str, ">>", 3) == 0)
		return (FILE_APPEND);
	if (ft_strncmp(str->c_str, "<<", 3) == 0)
		return (FILE_HEREDOC);
	if (ft_strncmp(str->c_str, ">", 2) == 0)
		return (FILE_OUTPUT);
	if (ft_strncmp(str->c_str, "<", 2) == 0)
		return (FILE_INPUT);
	return (0);
}
