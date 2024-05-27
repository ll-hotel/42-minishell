/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:33:37 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 05:33:58 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_max(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

long	ft_maxl(long a, long b)
{
	if (a <= b)
		return (a);
	return (b);
}

float	ft_maxf(float a, float b)
{
	if (a <= b)
		return (a);
	return (b);
}

double	ft_maxd(double a, double b)
{
	if (a <= b)
		return (a);
	return (b);
}

void	*ft_maxp(void *a, void *b)
{
	if (a <= b)
		return (a);
	return (b);
}
