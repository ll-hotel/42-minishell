/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:47:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 04:08:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

static unsigned long	_sep_count(const char *str, const char *seps);
static void				_free_arr(char **arr, unsigned long i);
static unsigned long	_substr(const char *str, const char *seps, char **arr, \
		unsigned long i);

char	**ft_splat(const char *str, const char *seps)
{
	const unsigned long	sep_count = _sep_count(str, seps);
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
		while (str[offset] && ft_strchr(seps, str[offset]))
			offset++;
		j = _substr(str + offset, seps, arr, i);
		i += 1;
		offset += j;
	}
	arr[i] = 0;
	return (arr);
}

static unsigned long	_sep_count(const char *str, const char *seps)
{
	unsigned long	r;
	unsigned long	j;

	r = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && ft_strchr(seps, str[j]))
			j++;
		r += (str[j] != 0);
		while (str[j] && !ft_strchr(seps, str[j]))
			j++;
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

static unsigned long	_substr(const char *str, const char *seps, char **arr, \
		unsigned long i)
{
	unsigned long	j;

	j = 0;
	while (str[j] && !ft_strchr(seps, str[j]))
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
