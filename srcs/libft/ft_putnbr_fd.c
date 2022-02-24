/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:21:02 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 12:32:09 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putrec(long long n, int fd)
{
	if (n)
	{
		ft_putrec(n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	tmp;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	tmp = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		tmp *= -1;
	}
	ft_putrec(tmp, fd);
}
