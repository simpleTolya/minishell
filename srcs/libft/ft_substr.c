/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:18:55 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 16:24:24 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_required_len(char const *s, unsigned int start, size_t len)
{
	size_t	req_len;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (0);
	req_len = 0;
	while (s[start + req_len] && req_len < len)
	{
		req_len++;
	}
	return (req_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	k;
	size_t	res_len;

	if (!s)
		return (0);
	res_len = ft_required_len(s, start, len);
	res = (char *) malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (0);
	if (!res_len)
	{
		res[0] = 0;
		return (res);
	}
	k = 0;
	while (s[start] && k < len)
	{
		res[k] = s[start];
		k++;
		start++;
	}
	res[k] = 0;
	return (res);
}
