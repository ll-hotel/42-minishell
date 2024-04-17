/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.82lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 01:34:31 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/02/23 03:42:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_bzero(void *s, unsigned long n)
{
	unsigned char	*p;

	p = s;
	if (n & 1)
		*(p++) = 0;
	if (n & 2)
		*((unsigned short *)p) = 0;
	p += n & 2;
	if (n & 4)
		*((unsigned int *)p) = 0;
	p += n & 4;
	while (n >= 8)
	{
		n -= 8;
		*((unsigned long long *)p) = 0;
		p += 8;
	}
	return (s);
}
