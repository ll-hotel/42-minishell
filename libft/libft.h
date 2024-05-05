/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 10:59:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "include/basics.h"
# include "include/ft_printf.h"
# include "include/ft_dprintf.h"
# include "include/get_next_line.h"
# include "include/vector.h"

void	*ft_realloc(void *p, unsigned long old_size, unsigned long n);
int		ft_strichr(char *str, int c);
int		ft_isspace(int c);
int		ft_isblank(int c);
void	*ft_memdup(void *p, unsigned long size);

#endif
