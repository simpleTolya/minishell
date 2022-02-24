/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_magic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:47:44 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:42:13 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

typedef struct s_vars
{
	t_string		var;
	t_string		n_str;
	unsigned int	i;
}	t_vars;

static void	ft_do_if_envvar(t_string *str, t_utils *util, t_vars *vars)
{
	if (str->c_str[vars->i + 1] && !ft_isspace(str->c_str[vars->i + 1])
		&& str->c_str[vars->i + 1] != '$' && str->c_str[vars->i + 1] != '"'
		&& str->c_str[vars->i + 1] != '\'')
	{
		vars->i++;
		while (str->c_str[vars->i] && !ft_isspace(str->c_str[vars->i])
			&& str->c_str[vars->i] != '$' && str->c_str[vars->i] != '"'
			&& str->c_str[vars->i] != '\'')
		{
			ft_str_append(&vars->var, str->c_str[vars->i]);
			vars->i++;
		}
		ft_replace_var_to_value(&vars->var, util);
		ft_str_paste(&vars->n_str, &vars->var, -1);
		ft_str_c_copy(&vars->var, "");
	}
	else
	{
		ft_str_append(&vars->n_str, '$');
		vars->i++;
	}
}

static void	ft_do_if_double_quote(t_string *str, t_utils *util, t_vars *vars)
{
	vars->i++;
	while (str->c_str[vars->i] != '"')
	{
		if (str->c_str[vars->i] == '$')
			ft_do_if_envvar(str, util, vars);
		else
		{
			ft_str_append(&vars->n_str, str->c_str[vars->i]);
			vars->i++;
		}
	}
	vars->i++;
}

void	ft_replace_magic(t_string *str, t_utils *util)
{
	t_vars	vars;

	ft_str_init(&vars.n_str, "");
	ft_str_init(&vars.var, "");
	vars.i = 0;
	while (vars.i < str->size)
	{
		if (str->c_str[vars.i] == '\'')
		{
			while (str->c_str[++vars.i] != '\'')
				ft_str_append(&vars.n_str, str->c_str[vars.i]);
			vars.i++;
		}
		else if (str->c_str[vars.i] == '"')
			ft_do_if_double_quote(str, util, &vars);
		else if (str->c_str[vars.i] == '$')
			ft_do_if_envvar(str, util, &vars);
		else
			ft_str_append(&vars.n_str, str->c_str[vars.i++]);
	}
	ft_str_copy(str, &vars.n_str);
	ft_str_clear(&vars.n_str);
	ft_str_clear(&vars.var);
}
