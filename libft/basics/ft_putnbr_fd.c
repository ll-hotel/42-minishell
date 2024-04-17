/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 03:17:56 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/27 05:49:59 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	char	s[11];
	short	log;
	int		i;

	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	log = 0;
	while (log < 11)
		s[log++] = 0;
	i = n;
	i *= (n >= 0) - (n < 0);
	s[--log] = '0';
	while (i)
	{
		s[log--] = (i % 10) + '0';
		i /= 10;
	}
	if (n < 0)
		s[log--] = '-';
	return (write(fd, s + log + (log < 10), 10 - log + (log == 10)));
}
