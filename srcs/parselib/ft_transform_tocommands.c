/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_tocommands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:15:44 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:50:53 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

static int	ft_do_if_twopipe(t_parse_object *p_obj,
		t_total_block *block, t_utils *util, t_list **lex_lst)
{
	t_command	*command;

	if (*lex_lst == 0)
	{
		ft_clear_block(block);
		return (ft_print_parse_error(UNEXPECTED_OROR_ERROR));
	}
	command = malloc(sizeof(t_command));
	command->flag = COMMAND_IF_BAD;
	if (ft_transform_lexemes_to_procblocks(command, lex_lst, util))
	{
		free(command);
		ft_lstclear(lex_lst, ft_clear_string);
		ft_clear_block(block);
		return (1);
	}
	ft_lstadd_back(&block->commands, ft_lstnew(command));
	ft_lstdelone(ft_lstpop_front(&p_obj->lexeme_lst), ft_clear_string);
	*lex_lst = 0;
	return (0);
}

static int	ft_do_if_twoand(t_parse_object *p_obj,
		t_total_block *block, t_utils *util, t_list **lex_lst)
{
	t_command	*command;

	if (*lex_lst == 0)
	{
		ft_clear_block(block);
		return (ft_print_parse_error(UNEXPECTED_ANDAND_ERROR));
	}
	command = malloc(sizeof(t_command));
	command->flag = COMMAND_IF_GOOD;
	if (ft_transform_lexemes_to_procblocks(command, lex_lst, util))
	{
		free(command);
		ft_lstclear(lex_lst, ft_clear_string);
		ft_clear_block(block);
		return (1);
	}
	ft_lstadd_back(&block->commands, ft_lstnew(command));
	ft_lstdelone(ft_lstpop_front(&p_obj->lexeme_lst), ft_clear_string);
	*lex_lst = 0;
	return (0);
}

static int	ft_do_last(t_parse_object *p_obj,
		t_total_block *block, t_utils *util, t_list **lex_lst)
{
	t_command	*command;

	(void) p_obj;
	if (*lex_lst)
	{
		command = malloc(sizeof(t_command));
		command->flag = COMMAND_END;
		if (ft_transform_lexemes_to_procblocks(command, lex_lst, util))
		{
			free(command);
			ft_lstclear(lex_lst, ft_clear_string);
			ft_clear_block(block);
			return (1);
		}
		ft_lstadd_back(&block->commands, ft_lstnew(command));
	}
	else
	{
		ft_clear_block(block);
		return (ft_print_parse_error(EXPECTED_COMMAND_ERROR));
	}
	return (0);
}

int	ft_transform_lexemes_to_commands(t_parse_object *p_obj,
		t_total_block *block, t_utils *util)
{
	t_list		*lex_lst;

	lex_lst = 0;
	while (p_obj->lexeme_lst)
	{
		if (ft_strncmp(((t_string *)p_obj->lexeme_lst->content)->c_str,
				"||", 3) == 0)
		{
			if (ft_do_if_twopipe(p_obj, block, util, &lex_lst))
				return (1);
		}
		else if (ft_strncmp(((t_string *)p_obj->lexeme_lst->content)->c_str,
				"&&", 3) == 0)
		{
			if (ft_do_if_twoand(p_obj, block, util, &lex_lst))
				return (1);
		}
		else
			ft_lstadd_back(&lex_lst, ft_lstpop_front(&p_obj->lexeme_lst));
	}
	if (ft_do_last(p_obj, block, util, &lex_lst))
		return (1);
	return (0);
}
