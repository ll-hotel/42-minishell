/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:32:14 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/31 17:50:33 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_heredoc(char *line, int *p_i)
{
	size_t	i;
	int		fd_pipe[2];
	char	*str;
	char	*end_sequence;

	i = 2;
	if (pipe(fd_pipe) == -1)
	{
		perror("miniChell");
		return (NULL);
	}
	while (ft_isblank(line[i]))
		i++;
	*p_i = i;
	end_sequence = line + i;
	i = 0;
	while (!ft_isblank(end_sequence[i]) && end_sequence[i])
		i++;
	end_sequence = ft_substr(end_sequence, 0, i);
	*p_i += i;
	str = readline("");
	while (!ft_strnstr(str, end_sequence, ft_strlen(str)))
	{
		write(fd_pipe[1], str, ft_strlen(str));
		str = readline("");
	}
	close(fd_pipe[1]);
	return (token_new((void *)(long) fd_pipe[0], TOKEN_HEREDOC));
}
