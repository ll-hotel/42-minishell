/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/24 17:34:57 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "include/basics.h"
# include "include/ft_printf.h"
# include "include/ft_dprintf.h"
# include "include/get_next_line.h"
# include "include/vector.h"

char	*ft_itoa_base(int n, const char *base_a);
void	*ft_realloc(void *p, unsigned long old_size, unsigned long n);

#endif
