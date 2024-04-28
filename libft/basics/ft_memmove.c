/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:10:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/24 17:36:21 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

static void	*ft_memcpy_from_right(void *dest, const void *src, unsigned long n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest + n - 1;
	s = (unsigned char *)src + n - 1;
	if (n & 1)
		*(d--) = *(s--);
	if (n & 2)
		*((unsigned short *)d) = *((unsigned short *)s);
	d -= n & 2;
	s -= n & 2;
	if (n & 4)
		*((unsigned int *)d) = *((unsigned int *)s);
	d -= n & 4;
	s -= n & 4;
	n >>= 3;
	while (n--)
	{
		*((unsigned long *)d) = *((unsigned long *)s);
		d -= 8;
		s -= 8;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, unsigned long n)
{
	if (!dest && !src)
		return (0);
	if (src < dest && dest < (src + n))
		ft_memcpy_from_right(dest, src, n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
