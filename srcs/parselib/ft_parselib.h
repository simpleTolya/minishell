/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parselib.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:39:52 by marmand           #+#    #+#             */
/*   Updated: 2022/02/03 23:58:04 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSELIB_H
# define FT_PARSELIB_H

# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../ft_process.h"
# include "../libstr/ft_string.h"
# include "../libft/libft.h"

# define EXPECTED_COMMAND_ERROR 300
# define SINGLE_QUOTES_ERROR 301
# define DOUBLE_QUOTES_ERROR 302
# define UNSUPPORTED_TOKEN_ERROR 303
# define UNEXPECTED_NEWLINE_ERROR 202
# define UNEXPECTED_GRT_ERROR 203
# define UNEXPECTED_GRTGRT_ERROR 204
# define UNEXPECTED_LSS_ERROR 205
# define UNEXPECTED_LSSLSS_ERROR 206
# define UNEXPECTED_AND_ERROR 207
# define UNEXPECTED_ANDAND_ERROR 208
# define UNEXPECTED_PIPE_ERROR 209
# define UNEXPECTED_OROR_ERROR 210
# define HOME_NOT_SET_ERROR 240
# define AMBIGUOUS_REDIRECT_ERROR 250
# define OLDPWD_NOT_SET_ERROR 242

enum e_command_flag
{
	COMMAND_END = 0,
	COMMAND_IF_GOOD = 1,
	COMMAND_IF_BAD = 2
};

enum e_file_flag
{
	FILE_INPUT		= 1,
	FILE_OUTPUT		= 2,
	FILE_APPEND		= 3,
	FILE_HEREDOC	= 4
};

typedef struct s_parse_object
{
	t_list		*lexeme_lst;
}	t_parse_object;

typedef struct s_file_info
{
	t_string			file_name;
	enum e_file_flag	file_flag;
}	t_file_info;

typedef struct s_process_block
{
	t_string	_path;
	char		**argv;
	t_file_info	*files;
	int			files_count;
	int			_fd_input;
	int			_fd_output;
}	t_process_block;

typedef struct s_command
{
	t_list				*process_blocks;
	enum e_command_flag	flag;
}	t_command;

typedef struct s_total_block
{
	t_list		*commands;
}	t_total_block;

typedef struct s_utils
{
	char	**env;
	int		last_process_code;
}	t_utils;

void	ft_change_home_dir(t_process_block *p_block, t_utils *util);
int		ft_get_var_value(char *var, t_utils *util, t_string *val);
int		ft_print_parse_error(int error_code);
void	ft_heredoc_paste_vars(char **line_ptr, t_utils *util);
int		ft_parse(const char *str, t_parse_object *p_obj);
int		ft_pobject_append_lexeme(t_parse_object *p_obj, const t_string *lexeme);
int		ft_parse_lexemes(const t_string *str, t_parse_object *p_obj);
int		ft_transform_lexemes_to_commands(t_parse_object *p_obj,
			t_total_block *block, t_utils *util);
int		ft_transform_lexemes_to_procblocks(t_command *command,
			t_list **lex_lst, t_utils *util);
int		ft_transform_words_to_procblock(t_process_block *p_block,
			t_list **words, t_utils *util);
void	ft_clear_block(void *block);
void	ft_clear_command(void *command);
void	ft_clear_pblock(void *p_block);
void	ft_clear_string(void *str);
void	ft_clear_pobj(t_parse_object *p_obj);
void	ft_clear_split_strs(char **str);
void	ft_clear_util(t_utils *util);
int		ft_get_path_to_process(const char *process_name,
			const char **paths, t_string *res);
void	ft_replace_var_to_value(t_string *var, t_utils *util);
int		ft_is_redir_sym(t_string *str);
void	ft_get_arguments(t_process_block *p_block, t_list **words);
void	ft_get_redirects(t_process_block *block, t_list **words);
int		ft_notcorrect_procblock(t_list **words);
void	ft_replace_magic_lst(t_list **lst, t_utils *util);
void	ft_replace_magic(t_string *str, t_utils *util);
void	ft_paste_wildcard_star(t_process_block *p_block, t_utils *util);

#endif
