/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:20:09 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/01 15:25:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_itoa(int n)
{
	const _Bool	is_negative = (n < 0);
	long		tmp;
	char		*val;
	short		len;
	short		i;

	len = ft_log_b(n, 10) + 1;
	val = ft_calloc(len + 1 + is_negative, sizeof(char));
	if (!val)
		return (0);
	i = len + is_negative;
	tmp = n * (!is_negative - is_negative);
	while (i-- > is_negative)
	{
		val[i] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (n < 0)
		val[0] = '-';
	return (val);
}
