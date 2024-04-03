/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:08:27 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/11/09 13:24:01 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	*last;

	p = (char *)s;
	last = 0;
	c = (char)c;
	while (*p)
	{
		if (*p == c)
			last = p++;
		while (*p && *p != c)
			p++;
	}
	if (!c)
		return (p);
	return (last);
}
