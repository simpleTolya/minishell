/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:08:05 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/04 21:24:08 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	init_child_struct(t_child *child, t_list *prcs)
{
	child->fifo[0][0] = -1;
	child->fifo[0][1] = -1;
	child->fifo[1][0] = -1;
	child->fifo[1][1] = -1;
	child->curr_pipe = 0;
	child->prc_iterator = 1;
	child->lst_size = ft_lstsize(prcs);
}

static int	wait_children(int ch_amount)
{
	int	i;
	int	status;

	i = -1;
	while (++i < ch_amount)
		wait(&status);
	signal(SIGINT, on_prog_sig);
	signal(SIGQUIT, SIG_IGN);
	unlink(".heredoc");
	if (WIFEXITED(status))
	{
		if (!status)
			return (0);
		if (WEXITSTATUS(status) == 255)
			return (127);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		else if (WTERMSIG(status) == 3)
			return (131);
		return (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

static void	exec_prc_blcks(t_process_block *prc, t_child *ch, t_utils *util)
{
	check_iostreams(prc, util);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	redir_streams(prc, ch, util);
	if (!if_builtins_in_child(prc->argv, util))
	{
		if (prc->argv[0] && execve(prc->_path.c_str, prc->argv,
				(char *const *) util->env) == -1)
			error_manage("minishell", util);
		else
			exit(0);
	}
}

static int	process_blocks(t_command *cmd, t_utils *util)
{
	t_list	*prc;
	t_child	child;

	prc = cmd->process_blocks;
	if (ft_lstsize(prc) == 1
		&& if_builtins(((t_process_block *)prc->content)->argv, util))
		return (0);
	init_child_struct(&child, cmd->process_blocks);
	while (prc)
	{
		if (pipe(child.fifo[child.curr_pipe]) == -1)
			error_manage("pipe", util);
		child.pid = fork();
		if (child.pid == -1)
			error_manage("fork", util);
		if (!child.pid)
			exec_prc_blcks(prc->content, &child, util);
		close(child.fifo[1 - child.curr_pipe][0]);
		close(child.fifo[child.curr_pipe][1]);
		child.curr_pipe = 1 - child.curr_pipe;
		prc = prc->next;
		child.prc_iterator++;
	}
	close(child.fifo[1 - child.curr_pipe][0]);
	return (wait_children(child.lst_size));
}

int	process_cmds(t_total_block *block, t_utils *util)
{
	t_list	*cmd;
	int		ex_fl;

	cmd = block->commands;
	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		ex_fl = process_blocks(cmd->content, util);
		if ((((t_command *)cmd->content)->flag == COMMAND_IF_GOOD && ex_fl == 0)
			|| (((t_command *)cmd->content)->flag == COMMAND_IF_BAD
				&& ex_fl))
			;
		else
		{
			util->last_process_code = ex_fl;
			return (ex_fl);
		}
		cmd = cmd->next;
	}
	return (0);
}
