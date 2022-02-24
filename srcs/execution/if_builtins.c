/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:43:50 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/03 23:43:52 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_exit(int status, t_utils *util)
{
	util->last_process_code = status;
	exit(status);
}

int	if_builtins(char **argv, t_utils *util)
{
	if (!argv[0])
		return (0);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
	{
		ft_cd(argv, util);
		return (1);
	}
	else if (ft_strncmp(argv[0], "export", 7) == 0)
	{
		ft_export(argv, util);
		return (1);
	}
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
	{
		ft_unset(argv, util);
		return (1);
	}
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		ft_exit(0, util);
	return (0);
}

int	if_builtins_in_child(char **argv, t_utils *util)
{
	if (!argv[0])
		return (0);
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		ft_echo(argv);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		ft_cd(argv, util);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		ft_env(argv, util);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		ft_export(argv, util);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		ft_unset(argv, util);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		ft_exit(0, util);
	else
		return (0);
	exit(0);
}

void	ft_update_shlvl(t_utils *util)
{
	t_string	shlvl;
	char		*num;
	int			i;

	i = 0;
	while (util->env[i])
	{
		if (ft_strncmp(util->env[i], "SHLVL=", 6) == 0)
		{
			num = ft_itoa(ft_atoi(util->env[i] + 6) + 1);
			free(util->env[i]);
			ft_str_init(&shlvl, num);
			ft_str_c_paste(&shlvl, "SHLVL=", 0);
			free(num);
			util->env[i] = shlvl.c_str;
			return ;
		}
		i++;
	}
	ft_str_init(&shlvl, "SHLVL=1");
	ft_export_add_var(&shlvl, util);
}
