/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_iostreams.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:19:56 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/03 23:45:45 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redir_streams(t_process_block *prc, t_child *ch, t_utils *util)
{
	if (ch->prc_iterator > 1)
	{
		if (dup2(ch->fifo[1 - ch->curr_pipe][0], STDIN_FILENO) == -1)
			error_manage("dup", util);
		close(ch->fifo[1 - ch->curr_pipe][0]);
	}
	if (ch->prc_iterator < ch->lst_size)
	{
		if (dup2(ch->fifo[ch->curr_pipe][1], STDOUT_FILENO) == -1)
			error_manage("dup", util);
		close(ch->fifo[ch->curr_pipe][0]);
		close(ch->fifo[ch->curr_pipe][1]);
	}
	if (prc->_fd_input != -1)
	{
		if (dup2(prc->_fd_input, STDIN_FILENO) == -1)
			error_manage("dup", util);
		close(prc->_fd_input);
	}
	if (prc->_fd_output != -1)
	{
		if (dup2(prc->_fd_output, STDOUT_FILENO) == -1)
			error_manage("dup", util);
		close(prc->_fd_output);
	}
}

static void	prc_heredoc_input(t_process_block *prc, const t_file_info *file,
	t_utils *util)
{
	char	*line;
	int		tmp_fd;

	signal(SIGINT, on_heredoc_sig);
	rl_catch_signals = 1;
	tmp_fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(file->file_name.c_str,
				line, file->file_name.size) == 0)
		{
			free(line);
			break ;
		}
		ft_heredoc_paste_vars(&line, util);
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(tmp_fd);
	prc->_fd_input = open(".heredoc", O_RDONLY);
}

static void	prc_file_output(t_process_block *prc,
	const t_file_info *file, t_utils *util)
{
	if (prc->_fd_output != -1)
		close(prc->_fd_output);
	if (file->file_flag == FILE_APPEND)
		prc->_fd_output = open(file->file_name.c_str,
				O_APPEND | O_WRONLY | O_CREAT, 0777);
	else if (file->file_flag == FILE_OUTPUT)
		prc->_fd_output = open(file->file_name.c_str,
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (prc->_fd_output < 0)
		error_manage("dup", util);
}

static void	prc_file_input(t_process_block *prc,
	const t_file_info *file, t_utils *util)
{
	if (prc->_fd_input != -1)
		close(prc->_fd_input);
	if (file->file_flag == FILE_HEREDOC)
		prc_heredoc_input(prc, file, util);
	else if (file->file_flag == FILE_INPUT)
		prc->_fd_input = open(file->file_name.c_str, O_RDONLY);
	if (prc->_fd_input < 0)
		error_manage("fd", util);
}

int	check_iostreams(t_process_block *prc, t_utils *util)
{
	int					i;
	const t_file_info	*file = prc->files;

	i = 0;
	if (!file)
		return (0);
	while (i < prc->files_count)
	{
		if (file[i].file_flag == FILE_INPUT
			|| file[i].file_flag == FILE_HEREDOC)
			prc_file_input(prc, &file[i], util);
		else if (file[i].file_flag == FILE_OUTPUT
			|| file[i].file_flag == FILE_APPEND)
			prc_file_output(prc, &file[i], util);
		else
			break ;
		i++;
	}
	return (0);
}
