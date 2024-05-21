/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:39:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/07 08:45:06 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_itoa_base(int n, const char *base_a)
{
	const unsigned char	is_negative = (n < 0);
	const unsigned char	base = ft_strlen(base_a);
	char				*n_a;
	long				tmp;
	short				i;

	i = ft_log_b(n, base) + 1;
	n_a = ft_calloc(i + 1 + is_negative, sizeof(char));
	if (!n_a)
		return (0);
	i += is_negative;
	tmp = n * (!is_negative - is_negative);
	while (i-- > is_negative)
	{
		n_a[i] = base_a[tmp % base];
		tmp /= base;
	}
	if (is_negative)
		n_a[0] = '-';
	return (n_a);
}
