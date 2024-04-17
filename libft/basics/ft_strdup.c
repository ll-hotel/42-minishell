/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:59:12 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/09 13:26:32 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char const *s)
{
	char	*p;
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	p = malloc(sizeof(char) * ++l);
	if (!p)
		return (0);
	while (l--)
		p[l] = s[l];
	return (p);
}
