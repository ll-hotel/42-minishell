/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/06 14:09:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredocking(int fd, char *delimiter);
static void	update_str(char *delimiter, char **str, int *len, int *delfound);

int	parser_heredoc(t_token *head, t_msh *msh)
{
	(void) msh;
	int		fd_pipe[2];

	while (head->next && head->next->type != TOKEN_HEREDOC)
		head = head->next;
	if (!head->next)
		return (1);
	if (pipe(fd_pipe) == -1)
	{
		perror("heredoc");
		return (0);
	}
	heredocking(fd_pipe[1], head->next->str);
	head->next->str = ft_free(head->next->str);
	head->next->fd = fd_pipe[0];
	return (1);
}

static void	heredocking(int fd, char *delimiter)
{
	char	*str;
	int		str_len;
	int		line_index;
	int		delimiter_found;

	line_index = 1;
	delimiter_found = 0;
	update_str(delimiter, &str, &str_len, &delimiter_found);
	while (str && !delimiter_found)
	{
		str[str_len] = '\n';
		write(fd, str, str_len + 1);
		free(str);
		update_str(delimiter, &str, &str_len, &delimiter_found);
	}
	if (!delimiter_found)
		ft_dprintf(2, "minishell: warning: here-document at line %d " \
				"delimited by end-of-file (wanted `%s')\n", \
				line_index, delimiter);
	close(fd);
	ft_free(str);
}

static void	update_str(char *delimiter, char **str, int *len, int *delfound)
{
	*str = readline("");
	*len = ft_strlen(*str);
	if (*str)
		*delfound = ft_strncmp(*str, delimiter, *len) == 0;
}
