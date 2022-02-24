/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 23:29:55 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 00:06:08 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	n_len;

	n_len = 0;
	if (n < 0)
		n_len++;
	if (n == 0)
		return (1);
	while (n)
	{
		n_len++;
		n /= 10;
	}
	return (n_len);
}

char	*ft_itoa(int n)
{
	char		*res;
	long long	tmp;
	int			i;

	i = ft_numlen(n);
	res = (char *) malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	tmp = n;
	res[0] = '0';
	if (tmp < 0)
	{
		res[0] = '-';
		tmp *= -1;
	}
	res[i] = 0;
	while (tmp)
	{
		res[i - 1] = '0' + tmp % 10;
		tmp /= 10;
		i--;
	}
	return (res);
}
