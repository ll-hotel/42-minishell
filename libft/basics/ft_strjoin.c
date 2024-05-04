/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:08:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/04 16:43:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	if (s1)
		ft_memmove(str, s1, s1_len);
	if (s2)
		ft_memmove(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = 0;
	return (str);
}
