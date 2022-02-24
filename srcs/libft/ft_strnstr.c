/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:40:40 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 13:44:58 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	haystack_len;
	size_t	needle_len;

	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)(haystack));
	i = 0;
	while (i + needle_len < haystack_len + 1 && i + needle_len - 1 < len)
	{
		k = 0;
		while (k < needle_len)
		{
			if (haystack[i + k] != needle[k])
				break ;
			k++;
		}
		if (k == needle_len)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (0);
}
