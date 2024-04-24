/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:06:07 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/16 11:07:45 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int	ft_log_b(int64_t n, int64_t base)
{
	int	log;

	log = 0;
	n /= base;
	while (n && ++log)
		n /= base;
	return (log);
}

int	ft_log_ub(uint64_t n, int64_t base)
{
	int	log;

	log = 0;
	n /= base;
	while (n && ++log)
		n /= base;
	return (log);
}
