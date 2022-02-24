/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 23:00:53 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 16:26:38 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_reslen(char const *s1, char const *set)
{
	char const	*last;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	last = ft_strchr(s1, 0);
	while (last > s1 && ft_strchr(set, *(last - 1)))
		last--;
	if (last >= s1)
		return (last - s1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (!s1 || !set)
		return (0);
	len = ft_reslen(s1, set);
	res = (char *) malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = 0;
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
