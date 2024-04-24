/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:47:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/24 17:37:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

static unsigned long	_sep_count(const char *str, char c)
{
	unsigned long	r;
	unsigned long	j;

	r = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == c)
			j += 1;
		r += (str[j] != 0);
		while (str[j] && str[j] != c)
			j += 1;
	}
	return (r);
}

static void	_free_arr(char **arr, unsigned long i)
{
	unsigned long	j;

	j = 0;
	while (j <= i)
		free(arr[j++]);
	free(arr);
}

static unsigned long	_substr(const char *str, char c, char **arr, \
		unsigned long i)
{
	unsigned long	j;

	j = 0;
	while (str[j] && str[j] != c)
		j++;
	arr[i] = malloc(sizeof(char) * (j + 1));
	if (!arr[i])
	{
		_free_arr(arr, i);
		return (0);
	}
	ft_strlcpy(arr[i], str, j + 1);
	return (j);
}

char	**ft_split(const char *str, char c)
{
	const unsigned long	sep_count = _sep_count(str, c);
	char				**arr;
	unsigned long		i;
	unsigned long		j;
	unsigned long		offset;

	if (!str)
		return (0);
	arr = malloc((sep_count + 1) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	offset = 0;
	while (str[offset] && i < sep_count)
	{
		while (str[offset] && str[offset] == c)
			offset++;
		j = _substr(str + offset, c, arr, i);
		i += 1;
		offset += j;
	}
	arr[i] = 0;
	return (arr);
}
