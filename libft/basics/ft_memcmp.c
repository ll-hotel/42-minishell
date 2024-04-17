/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:52:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/09 13:40:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, unsigned long long n)
{
	unsigned long long	i;
	const unsigned char	*p1 = (unsigned char *)s1;
	const unsigned char	*p2 = (unsigned char *)s2;

	i = 0;
	while (i < n && p1[i] == p2[i])
		i++;
	if (i < n)
		return (p1[i] - p2[i]);
	return (0);
}
