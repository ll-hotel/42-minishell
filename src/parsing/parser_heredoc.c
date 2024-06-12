/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/12 23:59:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_document(t_msh *msh, t_token *heredoc, int linex, int fds[2]);

int	parser_heredoc(t_token *head, t_msh *msh)
{
	int	fds[2];

	while (head->next)
	{
		head = head->next;
		if (head->type == TOKEN_HEREDOC)
			if (!here_document(msh, head, 0, fds))
				return (0);
	}
	return (1);
}

static int	here_document(t_msh *msh, t_token *heredoc, int linex, int fds[2])
{
	(void)msh;
	char	*line;
	int		found_delimiter;

	if (pipe(fds) == -1)
		return (perror("here-document"), 0);
	linex = 0;
	line = readline("> ");
	found_delimiter = (line && ft_strcmp(line, heredoc->str) == 0);
	while (line && !found_delimiter)
	{
		linex += 1;
		ft_putstr_fd(line, fds[1]);
		write(fds[1], "\n", 1);
		line = readline("> ");
		found_delimiter = (line && ft_strcmp(line, heredoc->str) == 0);
	}
	if (!found_delimiter)
		ft_dprintf(2, "minishell: warning: here-document at line %d " \
			"delimited by end-of-file (wanted `%s')\n", \
			linex, heredoc->str);
	close(fds[1]);
	heredoc->fd = fds[0];
	return (1);
}
