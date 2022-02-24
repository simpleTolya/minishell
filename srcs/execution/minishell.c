/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 08:32:44 by marmand           #+#    #+#             */
/*   Updated: 2022/02/04 21:25:48 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	ft_catch_continue(t_utils *util, t_parse_object *p_obj,
	t_total_block *p_block, char *line)
{
	add_history(line);
	if (ft_parse(line, p_obj))
	{
		free(line);
		return (1);
	}
	if (ft_transform_lexemes_to_commands(p_obj, p_block, util))
	{
		ft_clear_pobj(p_obj);
		free(line);
		return (1);
	}
	return (0);
}

void	ft_run(t_utils *util, t_parse_object *p_obj,
	t_total_block *p_block, char *line)
{
	signal(SIGINT, on_prog_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		p_obj->lexeme_lst = 0;
		p_block->commands = 0;
		rl_catch_signals = 0;
		line = readline("minishell> ");
		if (line == 0)
			return ;
		if (ft_is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (ft_catch_continue(util, p_obj, p_block, line))
			continue ;
		process_cmds(p_block, util);
		ft_clear_block(p_block);
		free(line);
	}
}

void	ft_init_util(t_utils *util, char **env)
{
	int	i;

	util->last_process_code = 0;
	i = 0;
	while (env[i])
		i++;
	util->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		util->env[i] = ft_strdup(env[i]);
		i++;
	}
	util->env[i] = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_utils			util;
	t_parse_object	p_obj;
	t_total_block	p_block;
	char			*line;

	(void) argc;
	(void) argv;
	line = NULL;
	ft_init_util(&util, env);
	ft_update_shlvl(&util);
	ft_run(&util, &p_obj, &p_block, line);
	return (0);
}
