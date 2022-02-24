/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_lexemes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:26:15 by marmand           #+#    #+#             */
/*   Updated: 2022/02/02 11:37:08 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

typedef struct s_vars
{
	unsigned int	i;
	int				flag;
	t_string		lexeme;
}	t_vars;

static int	ft_if_double_quote(const t_string *str, t_parse_object *p_obj,
	t_vars *vars)
{
	ft_pobject_append_lexeme(p_obj, &vars->lexeme);
	ft_str_c_copy(&vars->lexeme, "");
	ft_str_append(&vars->lexeme, str->c_str[vars->i++]);
	while (str->c_str[vars->i] && str->c_str[vars->i] != '"')
	{
		ft_str_append(&vars->lexeme, str->c_str[vars->i]);
		vars->i++;
	}
	if (!str->c_str[vars->i])
	{
		ft_clear_pobj(p_obj);
		ft_str_clear(&vars->lexeme);
		return (ft_print_parse_error(DOUBLE_QUOTES_ERROR));
	}
	ft_str_append(&vars->lexeme, str->c_str[vars->i]);
	ft_pobject_append_lexeme(p_obj, &vars->lexeme);
	ft_str_c_copy(&vars->lexeme, "");
	return (0);
}

static int	ft_if_single_quote(const t_string *str, t_parse_object *p_obj,
	t_vars *vars)
{
	ft_pobject_append_lexeme(p_obj, &vars->lexeme);
	ft_str_c_copy(&vars->lexeme, "");
	ft_str_append(&vars->lexeme, str->c_str[vars->i++]);
	while (str->c_str[vars->i] && str->c_str[vars->i] != '\'')
	{
		ft_str_append(&vars->lexeme, str->c_str[vars->i]);
		vars->i++;
	}
	if (!str->c_str[vars->i])
	{
		ft_clear_pobj(p_obj);
		ft_str_clear(&vars->lexeme);
		return (ft_print_parse_error(SINGLE_QUOTES_ERROR));
	}
	ft_str_append(&vars->lexeme, str->c_str[vars->i]);
	ft_pobject_append_lexeme(p_obj, &vars->lexeme);
	ft_str_c_copy(&vars->lexeme, "");
	return (0);
}

static void	ft_if_magic_char(const t_string *str, t_parse_object *p_obj,
	t_vars *vars, char mag)
{
	vars->flag = 1;
	ft_pobject_append_lexeme(p_obj, &vars->lexeme);
	ft_str_c_copy(&vars->lexeme, "");
	ft_str_append(&vars->lexeme, mag);
	if (str->c_str[vars->i + 1] == mag)
	{
		ft_str_append(&vars->lexeme, mag);
		vars->i++;
	}
	ft_pobject_append_lexeme(p_obj, &vars->lexeme);
	ft_str_c_copy(&vars->lexeme, "");
}

static int	ft_if_not_space(const t_string *str, t_parse_object *p_obj,
	t_vars *vars)
{
	if (vars->flag && str->c_str[vars->i] == '"')
	{
		if (ft_if_double_quote(str, p_obj, vars))
			return (1);
	}
	else if (vars->flag && str->c_str[vars->i] == '\'')
	{
		if (ft_if_single_quote(str, p_obj, vars))
			return (1);
	}
	else if (str->c_str[vars->i] == '<' || str->c_str[vars->i] == '>'
		|| str->c_str[vars->i] == '|' || str->c_str[vars->i] == '&')
		ft_if_magic_char(str, p_obj, vars, str->c_str[vars->i]);
	else
	{
		ft_str_append(&vars->lexeme, str->c_str[vars->i]);
		vars->flag = 0;
	}
	return (0);
}

int	ft_parse_lexemes(const t_string *str, t_parse_object *p_obj)
{
	t_vars	vars;

	ft_str_init(&vars.lexeme, "");
	vars.i = 0;
	vars.flag = 1;
	while (vars.i < str->size)
	{
		if (ft_isspace(str->c_str[vars.i]))
		{
			ft_pobject_append_lexeme(p_obj, &vars.lexeme);
			ft_str_c_copy(&vars.lexeme, "");
			vars.flag = 1;
		}
		else if (ft_if_not_space(str, p_obj, &vars))
			return (1);
		vars.i++;
	}
	if (vars.lexeme.size)
		ft_pobject_append_lexeme(p_obj, &vars.lexeme);
	ft_str_clear(&vars.lexeme);
	return (0);
}
