/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:39:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/17 15:27:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

int	handle_format(const char *f, va_list *args, int *count);
int	handle_string(const char f, va_list *args);
int	handle_number(const char f, va_list *args);
int	handle_special(const char f, va_list *args);

static int	to_next_symbol(const char *f)
{
	int	i;

	if (!f)
		return (0);
	i = 0;
	while (f[i] && f[i] != '%')
		i += 1;
	return (write(1, f, i));
}

int	ft_printf(const char *format, ...)
{
	const uint64_t	len = ft_strlen(format);
	va_list			args;
	uint64_t		l;
	int				count;
	int				tmp;

	va_start(args, format);
	l = 0;
	count = 0;
	tmp = 0;
	while (l < len)
	{
		tmp = to_next_symbol(format + l);
		l += tmp + 1;
		count += tmp;
		if (!format[l - 1])
			continue ;
		tmp = handle_format(format + l, &args, &count);
		if (tmp < 0)
			return (va_end(args), -1);
		l += tmp;
	}
	va_end(args);
	return (count);
}
