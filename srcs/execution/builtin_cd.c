/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:25:54 by hlaunch           #+#    #+#             */
/*   Updated: 2022/02/04 01:05:32 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_get_var_value(char *var, t_utils *util, t_string *val)
{
	int	i;
	int	_len;

	_len = ft_strlen(var);
	i = 0;
	while (util->env[i])
	{
		if (ft_strncmp(util->env[i], var, _len) == 0)
		{
			ft_str_c_substr(val, util->env[i],
				ft_strchr(util->env[i], '=') - util->env[i] + 1, -1);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_change_var_value(char *var, char *value, t_utils *util)
{
	int			i;
	int			_len;
	t_string	str;

	_len = ft_strlen(var);
	i = 0;
	while (util->env[i])
	{
		if (ft_strncmp(util->env[i], var, _len) == 0)
		{
			free(util->env[i]);
			ft_str_init(&str, var);
			ft_str_c_paste(&str, "=", -1);
			ft_str_c_paste(&str, value, -1);
			util->env[i] = str.c_str;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	cd_back_to_oldpath(t_string *new_pwd,
	t_string *curr_pwd, t_utils *util)
{
	if (ft_get_var_value("OLDPWD", util, new_pwd))
	{
		ft_clear_string(new_pwd);
		ft_clear_string(curr_pwd);
		ft_print_parse_error(OLDPWD_NOT_SET_ERROR);
		return ;
	}
	ft_get_var_value("PWD", util, curr_pwd);
	printf("%s\n", new_pwd->c_str);
	chdir(new_pwd->c_str);
	ft_change_var_value("PWD", new_pwd->c_str, util);
}

void	ft_cd(char **argv, t_utils *util)
{
	t_string	new_pwd;
	t_string	curr_pwd;

	ft_str_init(&new_pwd, 0);
	ft_str_init(&curr_pwd, 0);
	if (!argv[1])
	{
		ft_get_var_value("PWD", util, &curr_pwd);
		ft_get_var_value("HOME", util, &new_pwd);
		chdir(new_pwd.c_str);
		ft_change_var_value("PWD", new_pwd.c_str, util);
	}
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		cd_back_to_oldpath(&new_pwd, &curr_pwd, util);
	else
	{
		ft_get_var_value("PWD", util, &curr_pwd);
		chdir(argv[1]);
		ft_str_c_copy(&new_pwd, getcwd(0, 0));
		ft_change_var_value("PWD", new_pwd.c_str, util);
	}
	ft_change_var_value("OLDPWD", curr_pwd.c_str, util);
	ft_str_clear(&curr_pwd);
	ft_str_clear(&new_pwd);
}
