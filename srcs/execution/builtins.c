/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:25:54 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/04 00:05:32 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/param.h>

void	ft_echo(char	**argv)
{
	int		i;
	int		flag;

	if (!argv[1])
	{
		write(1, "\n", 1);
		return ;
	}
	i = 1;
	flag = 1;
	if (!ft_strncmp(argv[1], "-n", 3))
	{
		i++;
		flag = 0;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[++i])
			write(1, " ", 1);
	}
	if (flag == 1)
		write(1, "\n", 1);
}

void	ft_pwd(void)
{
	char	buf[MAXPATHLEN];
	int		i;

	i = 0;
	getcwd((char *)buf, MAXPATHLEN);
	while (buf[i])
		write(1, &buf[i++], 1);
	write(1, "\n", 1);
}

void	ft_env(char **argv, t_utils *util)
{
	int	i;

	(void) argv;
	i = 0;
	while (util->env[i])
	{
		printf("%s\n", util->env[i]);
		i++;
	}
}

static int	ft_must_unset(const char *arg, char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		if (ft_strncmp(arg, arr[i], ft_strlen(arr[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(char **argv, t_utils *util)
{
	int		i;
	int		_new_size;
	char	**new_env;

	if (!argv[1])
		return ;
	i = 0;
	_new_size = 0;
	while (util->env[i])
		if (!ft_must_unset(util->env[i++], argv))
			_new_size++;
	new_env = malloc(sizeof(char *) * (_new_size + 1));
	i = 0;
	_new_size = 0;
	while (util->env[i])
	{
		if (!ft_must_unset(util->env[i], argv))
			new_env[_new_size++] = ft_strdup(util->env[i]);
		i++;
	}
	new_env[_new_size] = 0;
	ft_clear_split_strs(util->env);
	util->env = new_env;
}
