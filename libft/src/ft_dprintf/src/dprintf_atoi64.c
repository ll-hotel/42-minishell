/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_atoi64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:20:05 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/17 21:34:24 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

void	ft_atoi64(char *out, int64_t n, const char *abase, uint8_t base)
{
	const uint16_t	log = ft_logb(n, base);
	const uint8_t	negative = n < 0;
	int64_t			tmp;
	uint16_t		i;

	tmp = (n + (n == (int64_t)0x8000000000000000));
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
	if ((uint64_t)n == 0x8000000000000000)
		out[10] += 1;
}

void	ft_atoui64(char *out, uint64_t n, const char *abase, uint8_t base)
{
	uint16_t	i;

	i = ft_logbu(n, base);
	out[i] = abase[n % base];
	i += (n != 0);
	while (i > 0)
	{
		out[--i] = abase[n % base];
		n /= base;
	}
}
