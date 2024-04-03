/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:08:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/07 20:27:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
}

static size_t	_strlen(const char *s)
{
	size_t	l;

	l = 0;
	if (s)
		while (s[l])
			l++;
	return (l);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*p;
	size_t	l;
	size_t	i;

	if (!s1 && !s2)
		return (0);
	l = _strlen(s1);
	i = _strlen(s2);
	p = malloc(sizeof(char) * (l + i + 1));
	if (!p)
		return (0);
	if (s1)
		_strcpy(p, s1);
	if (s2)
		_strcpy(p + l, s2);
	p[l + i] = 0;
	return (p);
}
