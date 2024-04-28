/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:41:09 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/02/28 23:57:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, unsigned long n)
{
	const unsigned short		b2 = ((c << 8) & 0xff00) | (c & 0xff);
	const unsigned int			b4 = (b2 << 16) | b2;
	const unsigned long long	b8 = ((unsigned long long)b4 << 32) | b4;
	unsigned char				*p;

	p = s;
	if (n & 1)
		*(p++) = c & 0xff;
	if (n & 2)
		*((unsigned short *)p) = b2;
	p += n & 2;
	if (n & 4)
		*((unsigned int *)p) = b4;
	p += n & 4;
	n >>= 3;
	while (n--)
	{
		*((unsigned long long *)p) = b8;
		p += 8;
	}
	return (s);
}
