/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:59:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/08 14:57:43 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	size_t	l;

	if (!s)
		return ;
	l = 0;
	while (s[l])
		l++;
	write(fd, s, l);
	write(fd, "\n", 1);
}
