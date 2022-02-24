/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:44:32 by marmand           #+#    #+#             */
/*   Updated: 2021/10/05 20:04:11 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*c_last;

	c_last = ft_strchr(s, c);
	if (!c_last)
		return (0);
	s = c_last;
	while (*s)
	{
		if (*s == ((char)c))
			c_last = (char *)s;
		s++;
	}
	if (*s == ((char)c))
		c_last = (char *)s;
	return (c_last);
}
