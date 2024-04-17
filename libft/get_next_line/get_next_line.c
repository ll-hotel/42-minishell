/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:31:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/24 17:20:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include "get_next_line.h"
#include <unistd.h>

static char	*append(t_line *line, unsigned long to_next, t_memory *memory)
{
	if (line->str && line->str[line->len - 1] == '\n')
		return (line->str);
	if (extend_line(&line->str, to_next + 1) == 0)
		return (0);
	ft_strlcpy(line->str + line->len, memory->str, to_next);
	ft_strlcpy(memory->str, memory->str + to_next, BUFFER_SIZE - to_next);
	memory->len -= to_next;
	return (line->str);
}

static _Bool	loop_step(t_line *line, unsigned long *to_next, \
		t_memory *memory, int fd)
{
	if (extend_line(&line->str, *to_next + 1) == 0)
		return (0);
	ft_strlcpy(line->str + line->len, memory->str, *to_next);
	line->len = ft_strlen(line->str);
	memory->len = readtomemory(fd, memory);
	*to_next = next_line(memory->str);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_memory	memory;
	t_line			line;
	unsigned long	to_next;

	if (BUFFER_SIZE <= 0 || read(fd, memory.str, 0) < 0)
		return (0);
	if (!memory.str[0] && readtomemory(fd, &memory) <= 0)
		return (0);
	line.str = 0;
	line.len = 0;
	to_next = next_line(memory.str);
	if (!to_next)
		return (0);
	while (to_next && !memory.str[to_next] && memory.len > 0)
	{
		if (!loop_step(&line, &to_next, &memory, fd))
			return (0);
		if (line.str[line.len - 1] == '\n')
			return (line.str);
	}
	if (memory.str[0])
		return (append(&line, to_next, &memory));
	return (line.str);
}
