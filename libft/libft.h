/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/01 13:49:53 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "src/basics.h"
# include "src/ft_printf.h"
# include "src/get_next_line.h"
# include "src/ft_dprintf/ft_dprintf.h"
# include "src/vector.h"

char	*ft_itoa_base(int n, const char *base_a);
void	*ft_realloc(void *p, uint64_t old_size, uint64_t n);

#endif
