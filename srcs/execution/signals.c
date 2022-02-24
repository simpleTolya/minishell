/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:21:10 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/03 23:21:11 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	error_manage(const char *error_msg, t_utils *utils)
{
	perror(error_msg);
	utils->last_process_code = -1;
	exit(-1);
}

void	on_prog_sig(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_clear_visible_line();
		rl_redisplay();
		signal(SIGINT, on_prog_sig);
	}
}

void	on_heredoc_sig(int num)
{
	(void) num;
	printf("\n");
	exit(1);
}
