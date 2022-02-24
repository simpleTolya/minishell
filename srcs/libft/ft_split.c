/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 23:13:23 by marmand           #+#    #+#             */
/*   Updated: 2021/10/06 16:28:45 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordnum(char const *s, char c)
{
	size_t	num;
	char	flag;

	if (!s)
		return (0);
	flag = 1;
	num = 0;
	while (*s)
	{
		if (*s != c && flag)
		{
			flag = 0;
			num++;
		}
		if (*s == c)
			flag = 1;
		s++;
	}
	return (num);
}

static char	*ft_create_word(char const *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *) malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	len = 0;
	while (s[len] && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = 0;
	return (word);
}

static void	*ft_clear(char **array, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	flag;
	size_t	word_i;

	res = (char **) malloc(sizeof(char *) * (ft_wordnum(s, c) + 1));
	if (!res || !s)
		return (0);
	flag = 1;
	word_i = 0;
	while (*s)
	{
		if (*s != c && flag)
		{
			res[word_i] = ft_create_word(s, c);
			if (!res[word_i])
				return (ft_clear(res, word_i));
			flag = 0;
			word_i++;
		}
		if (*s == c)
			flag = 1;
		s++;
	}
	res[word_i] = 0;
	return (res);
}
