/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:14:31 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 13:39:37 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;

	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	i = 0;
	while (dst_len + i + 1 < dstsize && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	if (dstsize != dst_len)
		dst[i + dst_len] = 0;
	while (src[i])
		i++;
	return (dst_len + i);
}
