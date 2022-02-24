/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_to_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaunch <hlaunch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:37:59 by marmand           #+#    #+#             */
/*   Updated: 2022/02/03 23:44:19 by hlaunch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parselib.h"

char	**find_env_path(const char **paths)
{
	int		i;
	char	**splitted_paths;
	char	*raw_paths;

	i = 0;
	raw_paths = NULL;
	splitted_paths = NULL;
	while (paths[i])
	{
		if (ft_strncmp("PATH=", paths[i], 5) == 0)
		{
			raw_paths = ft_substr(paths[i], 5, ft_strlen(paths[i]));
			break ;
		}
		i++;
	}
	if (!raw_paths)
		return (NULL);
	splitted_paths = ft_split(raw_paths, ':');
	free(raw_paths);
	return (splitted_paths);
}

int	get_full_path(const char *process_name, char **splitted_pths, t_string *res)
{
	int			i;
	t_string	tmp;

	i = 0;
	ft_str_init(&tmp, process_name);
	ft_str_c_paste(&tmp, "/", 0);
	while (splitted_pths[i])
	{
		ft_str_c_paste(&tmp, splitted_pths[i], 0);
		if (access(tmp.c_str, X_OK | F_OK) == 0)
		{
			ft_str_copy(res, &tmp);
			break ;
		}
		ft_str_erase(&tmp, 0, ft_strlen(splitted_pths[i]));
		i++;
	}
	i = 0;
	while (splitted_pths[i])
		free(splitted_pths[i++]);
	free(splitted_pths);
	ft_str_clear(&tmp);
	if (!res->c_str || res->c_str[0] == 0)
		return (-1);
	return (0);
}

int	ft_get_path_to_process(const char *process_name,
	const char **paths, t_string *res)
{
	char		**splitted_pths;

	splitted_pths = NULL;
	if (!process_name || !paths
		|| !res || !process_name[0])
		return (69);
	if (ft_strchr(process_name, '/'))
	{
		if (access(process_name, 0) == 0)
		{
			ft_str_c_copy(res, process_name);
			return (0);
		}
	}
	else
	{
		splitted_pths = find_env_path(paths);
		return (get_full_path(process_name, splitted_pths, res));
	}
	return (-1);
}
