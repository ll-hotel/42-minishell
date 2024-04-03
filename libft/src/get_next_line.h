/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:44:04 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/12/07 19:39:34 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_memory
{
	char			str[BUFFER_SIZE + 1];
	unsigned long	len;
}	t_memory;

typedef struct s_line
{
	char			*str;
	unsigned long	len;
}	t_line;

unsigned long	extend_line(char **s, int sup_size);
unsigned long	next_line(char *s);
unsigned long	readtomemory(int fd, t_memory *memory);
char			*get_next_line(int fd);

#endif
