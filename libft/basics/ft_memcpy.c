/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:39:57 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/01 14:28:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

void	*ft_memcpy(void *dest, const void *src, uint64_t n)
{
	uint8_t	*d;
	uint8_t	*s;

	d = (uint8_t *)dest;
	s = (uint8_t *)src;
	if (n & 1)
		*(d++) = *(s++);
	if (n & 2)
		*((uint16_t *)d) = *((uint16_t *)s);
	d += n & 2;
	s += n & 2;
	if (n & 4)
		*((uint32_t *)d) = *((uint32_t *)s);
	d += n & 4;
	s += n & 4;
	n >>= 3;
	while (n--)
	{
		*((uint64_t *)d) = *((uint64_t *)s);
		d += 8;
		s += 8;
	}
	return (dest);
}
