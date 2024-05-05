/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:57:07 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 10:59:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

void	*ft_memdup(void *p, unsigned long size)
{
	void	*d;

	d = malloc(size);
	if (d)
		ft_memmove(d, p, size);
	return (d);
}
