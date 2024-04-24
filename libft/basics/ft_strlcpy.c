/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:05 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/16 17:13:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long	ft_strlcpy(char *dest, const char *src, unsigned long size)
{
	unsigned long	i;

	i = -1;
	if (size)
	{
		while (++i < size - 1 && src[i])
			dest[i] = src[i];
		dest[i] = 0;
	}
	while (src[++i])
		;
	return (i);
}
