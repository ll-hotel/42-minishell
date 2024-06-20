/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lrichaud-get_next_line.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:09:17 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/20 00:20:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRICHAUD_GET_NEXT_LINE_H
# define LRICHAUD_GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft.h"

char	*get_next_line(int fd);

#endif
