/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:17:28 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/08 16:05:44 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			i;
	size_t			bytes;

	bytes = nmemb * size;
	if ((bytes < nmemb && size) || (bytes < size && nmemb))
		return (0);
	p = malloc(bytes);
	if (!p)
		return (0);
	i = 0;
	while (i < bytes)
		p[i++] = 0;
	return (p);
}
