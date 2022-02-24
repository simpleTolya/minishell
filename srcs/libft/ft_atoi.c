/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:31:26 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 15:53:31 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_numlen(const char *s)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(*s))
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_check_overlong(const char *s)
{
	int		sgn;
	size_t	len;

	sgn = -1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sgn = 0;
		s++;
	}
	len = ft_numlen(s);
	if (len > 19)
		return (sgn);
	if (sgn == -1 && len == 19 && ft_strncmp(s, "9223372036854775807", 19) > 0)
		return (sgn);
	if (sgn == 0 && len == 19 && ft_strncmp(s, "9223372036854775808", 19) > 0)
		return (sgn);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	while (ft_space(*str))
		str++;
	sign = ft_check_overlong(str);
	if (sign != 1)
		return (sign);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (ft_isdigit(*str))
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	res *= sign;
	return ((int) res);
}
