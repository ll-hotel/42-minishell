/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:17:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/24 18:10:03 by ll-hotel         ###   ########.fr       */
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
