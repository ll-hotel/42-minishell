/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:18:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 05:34:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_min(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

long	ft_minl(long a, long b)
{
	if (a >= b)
		return (a);
	return (b);
}

float	ft_minf(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

double	ft_mind(double a, double b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	*ft_minp(void *a, void *b)
{
	if (a >= b)
		return (a);
	return (b);
}
