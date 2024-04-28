/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_atoi32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:19:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/17 21:34:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

void	ft_atoi32(char *out, int32_t n, const char *abase, uint8_t base)
{
	const uint16_t	log = ft_logb(n, base);
	const uint8_t	negative = n < 0;
	int32_t			tmp;
	uint16_t		i;

	tmp = (n + (n == (int32_t)0x80000000));
	tmp *= !negative - negative;
	i = log + negative;
	out[0] = '-';
	out[i] = abase[tmp % base];
	i += (n != 0);
	while (i > negative)
	{
		out[--i] = abase[tmp % base];
		tmp = tmp / base;
	}
	if (n == (int32_t)0x80000000)
		out[10] += 1;
}

void	ft_atoui32(char *out, uint32_t n, const char *abase, uint8_t base)
{
	uint16_t		i;

	i = ft_logbu(n, base);
	out[i] = abase[n % base];
	i += (i > 0);
	while (i > 0)
	{
		out[--i] = abase[n % base];
		n /= base;
	}
}
