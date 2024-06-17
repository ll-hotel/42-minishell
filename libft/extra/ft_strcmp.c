/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:51:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/12 21:55:49 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned long long	i1;
	unsigned long long	i2;

	if (!s1 && !s2)
		return (0);
	i1 = 0;
	i2 = 0;
	while (s1[i1] && s1[i1] == s2[i2])
	{
		i1 += 1;
		i2 += 1;
	}
	return ((s1[i1] - s2[i2]) & 0xff);
}
