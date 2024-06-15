/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/16 01:46:23 by ll-hotel         ###   ########.fr       */
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
char	**ft_splat(const char *str, const char *seps);
int		ft_min(int a, int b);
long	ft_minl(long a, long b);
float	ft_minf(float a, float b);
double	ft_mind(double a, double b);
void	*ft_minp(void *a, void *b);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtok(char *str, const char *delim);

#endif
