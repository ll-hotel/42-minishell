/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:17:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/17 21:35:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

uint8_t	ft_logb(int64_t n, uint8_t base)
{
	uint8_t	l;

	l = 0;
	n /= base;
	while (n)
	{
		n /= base;
		l += 1;
	}
	return (l);
}

uint8_t	ft_logbu(uint64_t n, uint8_t base)
{
	uint8_t	l;

	l = 0;
	n /= base;
	while (n)
	{
		n /= base;
		l += 1;
	}
	return (l);
}

void	*ft_bzero(void *s, unsigned long n)
{
	unsigned char	*p;

	p = s;
	if (n & 1)
		*(p++) = 0;
	if (n & 2)
		*((unsigned short *)p) = 0;
	p += n & 2;
	if (n & 4)
		*((unsigned int *)p) = 0;
	p += n & 4;
	while (n >= 8)
	{
		n -= 8;
		*((unsigned long long *)p) = 0;
		p += 8;
	}
	return (s);
}
