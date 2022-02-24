/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 07:35:53 by marmand           #+#    #+#             */
/*   Updated: 2022/02/03 23:58:44 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	init_strings(t_string *var,
	t_string *tmp, const t_string *cmd, int i)
{
	ft_str_init(var, "");
	ft_str_substr(var, cmd, 0, i);
	ft_str_init(tmp, "");
}

void	ft_export_add_var(const t_string *str, t_utils *util)
{
	char	**n_env;
	int		_size;

	_size = 0;
	while (util->env[_size])
		_size++;
	n_env = malloc(sizeof(char *) * (_size + 2));
	_size = 0;
	while (util->env[_size])
	{
		n_env[_size] = ft_strdup(util->env[_size]);
		_size++;
	}
	n_env[_size] = ft_strdup(str->c_str);
	n_env[_size + 1] = 0;
	ft_clear_split_strs(util->env);
	util->env = n_env;
}

static void	ft_export_equal(const t_string *cmd, t_utils *util)
{
	const int	sep_index = ft_str_c_find(cmd, "=");
	t_string	var;
	int			i;
	t_string	tmp;

	init_strings(&var, &tmp, cmd, sep_index);
	i = -1;
	while (util->env[++i])
	{
		if (ft_strncmp(var.c_str, util->env[i], var.size) == 0)
		{
			ft_str_c_copy(&tmp, util->env[i]);
			ft_str_erase(&tmp, var.size + 1, -1);
			ft_str_substr(&var, cmd, sep_index + 1, -1);
			ft_str_paste(&tmp, &var, -1);
			free(util->env[i]);
			util->env[i] = tmp.c_str;
			ft_str_clear(&var);
			return ;
		}
	}
	ft_export_add_var(cmd, util);
	ft_str_clear(&var);
	ft_str_clear(&tmp);
}

static void	ft_export_equalplus(const t_string *cmd, t_utils *util)
{
	const int	sep_index = ft_str_c_find(cmd, "+=");
	t_string	var;
	int			i;
	t_string	tmp;

	init_strings(&var, &tmp, cmd, sep_index);
	i = -1;
	while (util->env[++i])
	{
		if (ft_strncmp(var.c_str, util->env[i], var.size) == 0)
		{
			ft_str_c_copy(&tmp, util->env[i]);
			ft_str_substr(&var, cmd, sep_index + 2, -1);
			ft_str_paste(&tmp, &var, -1);
			free(util->env[i]);
			util->env[i] = tmp.c_str;
			ft_str_clear(&var);
			return ;
		}
	}
	ft_str_copy(&tmp, cmd);
	ft_str_erase(&tmp, ft_str_c_find(&tmp, "+"), 1);
	ft_export_add_var(&tmp, util);
	ft_str_clear(&var);
	ft_str_clear(&tmp);
}

void	ft_export(char **argv, t_utils *util)
{
	t_string	arg;
	int			i;

	ft_str_init(&arg, "");
	i = 1;
	while (argv[i])
	{
		ft_str_c_copy(&arg, argv[i]);
		if (ft_str_c_find(&arg, "+=") != -1)
			ft_export_equalplus(&arg, util);
		else if (ft_str_c_find(&arg, "=") != -1)
			ft_export_equal(&arg, util);
		i++;
	}
	ft_str_clear(&arg);
}
