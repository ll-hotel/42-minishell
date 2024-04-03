/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:32:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/17 21:35:14 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

static int	ft_worker(const char type, uint64_t arg, t_buffer *buffer);

int	ft_specifier(const char *format, va_list args, t_buffer *buffer)
{
	const char	type = *format;
	uint64_t	arg;

	if (type == '%')
		arg = (uint64_t) '%';
	else if (type == 'c' || type == 'd' || type == 'i')
		arg = (uint64_t)va_arg(args, int32_t);
	else if (type == 'x' || type == 'X' || type == 'u')
		arg = (uint64_t)va_arg(args, uint32_t);
	else if (type == 's' || type == 'p')
		arg = (uint64_t)va_arg(args, void *);
	else
		return (0);
	return (ft_worker(type, arg, buffer));
}

static int	ft_worker(const char type, uint64_t arg, t_buffer *buffer)
{
	char	tmp_arr[21];
	int		ret_val;

	ft_bzero(tmp_arr, 21);
	if (type == 's')
		return (ft_string(buffer, buffer->fd, (char *)arg));
	ret_val = 0;
	if (type == '%' || type == 'c')
		return (ft_char(buffer, buffer->fd, (char)arg));
	if (type == 'd' || type == 'i')
		ft_atoi32(tmp_arr, (int32_t)arg, "0123456789", 10);
	else if (type == 'u')
		ft_atoui32(tmp_arr, (uint32_t)arg, "0123456789", 10);
	else if (type == 'x')
		ft_atoui32(tmp_arr, (uint32_t)arg, "0123456789abcdef", 16);
	else if (type == 'X')
		ft_atoui32(tmp_arr, (uint32_t)arg, "0123456789ABCDEF", 16);
	else if (type == 'p')
		ret_val = ft_pointer(tmp_arr, buffer, buffer->fd, arg);
	ret_val += ft_buffer_cat(buffer, buffer->fd, tmp_arr);
	return (ret_val);
}
