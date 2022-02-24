/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_toprocblocks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:09:26 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:51:27 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

static int	ft_if_pipe(t_command *command, t_list **lex_lst,
	t_utils *util, t_list **word_lst)
{
	t_process_block	*p_block;

	if (*word_lst == 0)
	{
		ft_clear_command(command);
		return (ft_print_parse_error(UNEXPECTED_PIPE_ERROR));
	}
	p_block = malloc(sizeof(t_process_block));
	if (ft_transform_words_to_procblock(p_block, word_lst, util))
	{
		free(p_block);
		ft_lstclear(word_lst, ft_clear_string);
		ft_clear_command(command);
		return (1);
	}
	ft_lstclear(word_lst, ft_clear_string);
	ft_lstadd_back(&command->process_blocks, ft_lstnew(p_block));
	ft_lstdelone(ft_lstpop_front(lex_lst), ft_clear_string);
	*word_lst = 0;
	return (0);
}

static int	ft_do_last(t_command *command, t_list **lex_lst,
	t_utils *util, t_list **word_lst)
{
	t_process_block	*p_block;

	(void) lex_lst;
	if (*word_lst)
	{
		p_block = malloc(sizeof(t_process_block));
		if (ft_transform_words_to_procblock(p_block, word_lst, util))
		{
			free(p_block);
			ft_lstclear(word_lst, ft_clear_string);
			ft_clear_command(command);
			return (1);
		}
		ft_lstclear(word_lst, ft_clear_string);
		ft_lstadd_back(&command->process_blocks, ft_lstnew(p_block));
	}
	else
	{
		ft_clear_command(command);
		return (ft_print_parse_error(EXPECTED_COMMAND_ERROR));
	}
	return (0);
}

int	ft_transform_lexemes_to_procblocks(t_command *command, t_list **lex_lst,
	t_utils *util)
{
	t_list			*word_lst;

	command->process_blocks = 0;
	word_lst = 0;
	while (*lex_lst)
	{
		if (ft_strncmp(((t_string *)(*lex_lst)->content)->c_str, "|", 2) == 0)
		{
			if (ft_if_pipe(command, lex_lst, util, &word_lst))
				return (1);
		}
		else
			ft_lstadd_back(&word_lst, ft_lstpop_front(lex_lst));
	}
	if (ft_do_last(command, lex_lst, util, &word_lst))
		return (1);
	return (0);
}
