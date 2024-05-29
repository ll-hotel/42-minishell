/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:10:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 18:53:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

static void	*ft_memcpy_from_right(void *dest, const void *src, uint64_t n)
{
	uint8_t	*d;
	uint8_t	*s;

	d = (uint8_t *)dest + n - 1;
	s = (uint8_t *)src + n - 1;
	if (n & 1)
		*(d--) = *(s--);
	if (n & 2)
		*((uint16_t *)d) = *((uint16_t *)s);
	d -= n & 2;
	s -= n & 2;
	if (n & 4)
		*((uint32_t *)d) = *((uint32_t *)s);
	d -= n & 4;
	s -= n & 4;
	n >>= 3;
	while (n--)
	{
		*((uint64_t *)d) = *((uint64_t *)s);
		d -= 8;
		s -= 8;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, uint64_t n)
{
	if (!dest && !src)
		return (0);
	if (src < dest && dest < (src + n))
		ft_memcpy_from_right(dest, src, n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
