/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:30:54 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/04 00:15:00 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parselib/ft_parselib.h"

typedef struct t_data
{
	pid_t	pid;
	int		fifo[2][2];
	int		curr_pipe;
	int		prc_iterator;
	int		lst_size;
}	t_child;

void	on_heredoc_sig(int num);
void	on_prog_sig(int num);
void	error_manage(const char *error_msg, t_utils *utils);
void	ft_unset(char **argv, t_utils *util);
void	ft_env(char **argv, t_utils *util);
void	ft_pwd(void);
void	ft_echo(char	**argv);
void	ft_export(char **argv, t_utils *util);
void	ft_cd(char **argv, t_utils *util);
void	ft_exit(int status, t_utils *util);
void	redir_streams(t_process_block *prc, t_child *ch, t_utils *util);
void	ft_export_add_var(const t_string *str, t_utils *util);
int		process_cmds(t_total_block *block, t_utils *util);
int		if_builtins_in_child(char **argv, t_utils *util);
int		if_builtins(char **argv, t_utils *util);
int		check_iostreams(t_process_block *prc, t_utils *util);
void	ft_update_shlvl(t_utils *util);

#endif