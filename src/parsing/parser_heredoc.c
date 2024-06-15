/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/15 18:47:48 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sighandler(int signal);
static int	here_document(t_msh *msh, t_token *heredoc, int linex, int fds[2]);

int	parser_heredoc(t_token *head, t_msh *msh)
{
	int	fds[2];
	int	std_in;
	int	ongoing;

	signal(SIGINT, heredoc_sighandler);
	std_in = dup(0);
	if (std_in == -1)
		return (perror("here-document"), 0);
	ongoing = 1;
	while (head->next && ongoing)
	{
		head = head->next;
		if (head->type == TOKEN_HEREDOC)
			ongoing = here_document(msh, head, 0, fds);
	}
	if (dup2(std_in, 0) == -1)
		return (perror("here-document"), 0);
	close(std_in);
	signal_gestionnary();
	return (ongoing);
}

static int	here_document(t_msh *msh, t_token *heredoc, int linex, int fds[2])
{
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
		ft_dprintf(fds[1], "%s\n", line);
		line = readline("> ");
		found_delimiter = (line && ft_strcmp(line, heredoc->str) == 0);
	}
	if (!found_delimiter)
		ft_dprintf(2, "minishell: warning: here-document at line %d " \
			"delimited by end-of-file (wanted `%s')\n", \
			linex, heredoc->str);
	close(fds[1]);
	heredoc->fd = fds[0];
	if (!ft_strchr(heredoc->str, '\'') && !ft_strchr(heredoc->str, '\"') && \
			heredoc_expand(msh, fds[0], &heredoc->fd) == 0)
		return (0);
	return (1);
}

static void	heredoc_sighandler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		msh_status_set(130);
		close(0);
	}
}
