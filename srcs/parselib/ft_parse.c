/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:40:52 by marmand           #+#    #+#             */
/*   Updated: 2022/02/01 21:03:07 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

static int	ft_check_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				return (ft_print_parse_error(DOUBLE_QUOTES_ERROR));
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (ft_print_parse_error(SINGLE_QUOTES_ERROR));
		}
		i++;
	}
	return (0);
}

int	ft_parse(const char *str, t_parse_object *p_obj)
{
	t_string	_str;

	if (ft_check_quote(str))
		return (1);
	if (ft_str_init(&_str, str))
		return (1);
	if (ft_parse_lexemes(&_str, p_obj))
	{
		ft_str_clear(&_str);
		return (1);
	}
	ft_str_clear(&_str);
	return (0);
}
