/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:33:54 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/02/23 03:43:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned long long	_strlen(const char *s)
{
	unsigned long long	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

unsigned long long	ft_strlcat(char *dst, const char *src, \
		unsigned long long size)
{
	const unsigned long long	len_dst = _strlen(dst);
	const unsigned long long	len_src = _strlen(src);
	unsigned long long			l;
	unsigned long long			i;

	l = 0;
	if (!size)
		return (len_src);
	while (l < size && dst[l])
		l++;
	i = 0;
	while (l < size - 1 && src[i])
		dst[l++] = src[i++];
	if (len_dst <= size)
		dst[l] = 0;
	if (size < len_dst)
		return (size + len_src);
	return (len_dst + len_src);
}
