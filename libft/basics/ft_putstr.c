/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:45:50 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/06 16:10:30 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	char	buf[1024];
	short	size;

	size = 0;
	while (*str)
	{
		if (size == 1024)
		{
			write(1, buf, size);
			size = 0;
		}
		buf[size++] = *str;
		if (*str == '\n')
		{
			write(1, buf, size);
			size = 0;
		}
		str++;
	}
	if (size)
		write(1, buf, size);
}
