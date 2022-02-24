/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:31:22 by marmand           #+#    #+#             */
/*   Updated: 2022/02/01 18:06:45 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

static void	ft_print_parse_error2(int error_code)
{
	if (error_code == UNEXPECTED_OROR_ERROR)
		write(2, "syntax error near unexpected token `||'\n", 40);
	else if (error_code == UNEXPECTED_PIPE_ERROR)
		write(2, "syntax error near unexpected token `|'\n", 39);
	else if (error_code == UNSUPPORTED_TOKEN_ERROR)
		write(2, "unsupported token\n", 18);
	else if (error_code == HOME_NOT_SET_ERROR)
		write(2, "cd: HOME not set\n", 17);
	else if (error_code == AMBIGUOUS_REDIRECT_ERROR)
		write(2, "*: ambiguous redirect\n", 22);
}

int	ft_print_parse_error(int error_code)
{
	write(2, "minishell: ", 11);
	if (error_code == EXPECTED_COMMAND_ERROR)
		write(2, "syntax error: command expected\n", 31);
	else if (error_code == SINGLE_QUOTES_ERROR)
		write(2, "syntax error: expected `'`\n", 27);
	else if (error_code == DOUBLE_QUOTES_ERROR)
		write(2, "syntax error: expected `\"`\n", 27);
	else if (error_code == UNEXPECTED_NEWLINE_ERROR)
		write(2, "syntax error near unexpected token `newline'\n", 45);
	else if (error_code == UNEXPECTED_AND_ERROR)
		write(2, "syntax error near unexpected token `&'\n", 39);
	else if (error_code == UNEXPECTED_ANDAND_ERROR)
		write(2, "syntax error near unexpected token `&&'\n", 40);
	else if (error_code == UNEXPECTED_GRT_ERROR)
		write(2, "syntax error near unexpected token `>'\n", 39);
	else if (error_code == UNEXPECTED_GRTGRT_ERROR)
		write(2, "syntax error near unexpected token `>>'\n", 40);
	else if (error_code == UNEXPECTED_LSS_ERROR)
		write(2, "syntax error near unexpected token `<'\n", 39);
	else if (error_code == UNEXPECTED_LSSLSS_ERROR)
		write(2, "syntax error near unexpected token `<<'\n", 40);
	ft_print_parse_error2(error_code);
	return (1);
}
