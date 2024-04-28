/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:50 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/16 16:06:08 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static _Bool	_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

static _Bool	_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

long	ft_atol(const char *nptr)
{
	long			r;
	char			sign;
	unsigned int	i;

	if (!nptr)
		return (0);
	i = 0;
	while (_isspace(nptr[i]))
		i++;
	if (!nptr[i])
		return (0);
	sign = (nptr[i] == '-');
	i += ((nptr[i] == '-') || (nptr[i] == '+'));
	r = 0;
	while (_isnum(nptr[i]))
		r = 10 * r + nptr[i++] - '0';
	return (r * (1 - 2 * sign));
}

int	ft_atoi(const char *nptr)
{
	int				r;
	char			sign;
	unsigned int	i;

	if (!nptr)
		return (0);
	i = 0;
	while (_isspace(nptr[i]))
		i++;
	if (!nptr[i])
		return (0);
	sign = (nptr[i] == '-');
	i += ((nptr[i] == '-') || (nptr[i] == '+'));
	r = 0;
	while (_isnum(nptr[i]))
		r = 10 * r + nptr[i++] - '0';
	return (r * (1 - 2 * sign));
}
