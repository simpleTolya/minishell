/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixing_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:34:31 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 10:53:18 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

typedef struct s_vars
{
	t_string		var;
	t_string		n_str;
	unsigned int	i;
}	t_vars;

static void	ft_if_maybe_envvar(t_string *str, t_utils *util, t_vars *vars)
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

static void	ft_replace_magic_heredoc(t_string *str, t_utils *util)
{
	t_vars	vars;

	ft_str_init(&vars.n_str, "");
	ft_str_init(&vars.var, "");
	vars.i = 0;
	while (vars.i < str->size)
	{
		if (str->c_str[vars.i] == '$')
			ft_if_maybe_envvar(str, util, &vars);
		else
		{
			ft_str_append(&vars.n_str, str->c_str[vars.i]);
			vars.i++;
		}
	}
	ft_str_clear(&vars.var);
	ft_str_copy(str, &vars.n_str);
	ft_str_clear(&vars.n_str);
}

void	ft_heredoc_paste_vars(char **line_ptr, t_utils *util)
{
	t_string	str;

	ft_str_init(&str, *line_ptr);
	ft_replace_magic_heredoc(&str, util);
	free(*line_ptr);
	*line_ptr = str.c_str;
}
