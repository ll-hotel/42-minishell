/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:28:44 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/09 14:13:46 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	len *= start <= l;
	if (len > l - start)
		len = l - start;
	if (len == l - start)
		p = malloc(sizeof(char) * (l - start + 1));
	else
		p = malloc(sizeof(char) * (len + 1));
	if (!p || !s)
		return (0);
	i = -1;
	while (++i < len && s[start + i])
		p[i] = s[start + i];
	p[i] = 0;
	return (p);
}
