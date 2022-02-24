/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_total_block.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:34:35 by marmand           #+#    #+#             */
/*   Updated: 2022/02/01 22:56:53 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

static void	ft_clear_pblock2(void *p_block)
{
	ft_clear_pblock(p_block);
	free(p_block);
}

static void	ft_clear_command2(void *command)
{
	ft_lstclear(&((t_command *)command)->process_blocks, ft_clear_pblock2);
	free(command);
}

void	ft_clear_command(void *command)
{
	ft_lstclear(&((t_command *)command)->process_blocks, ft_clear_pblock2);
}

void	ft_clear_pobj(t_parse_object *p_obj)
{
	ft_lstclear(&p_obj->lexeme_lst, ft_clear_string);
}

void	ft_clear_block(void *block)
{
	ft_lstclear(&((t_total_block *)block)->commands, ft_clear_command2);
}
