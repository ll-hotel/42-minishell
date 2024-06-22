/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/21 19:02:00 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static char	*loop_body(int linex, int fd[2], _Bool *found_delim, char *delim);
static void	heredoc_sighandler(int signal);
static int	here_document(t_ch *ch, t_token *heredoc, int linex, int fds[2]);

int	parser_heredoc(t_token *head, t_ch *ch)
{
	int		fds[2];
	int		ongoing;
	int		std_in;

	ch_signal(SIGINT, heredoc_sighandler);
	std_in = dup(0);
	if (std_in == -1)
		return (perror("miniChell"), 0);
	ongoing = 1;
	while (head->next && ongoing)
	{
		head = head->next;
		if (head->type == TOKEN_HEREDOC)
		{
			if (pipe(fds) == -1)
				return (perror("here-document"), 0);
			ongoing = here_document(ch, head, 0, fds);
			head->str = ft_free(head->str);
		}
	}
	if (dup2(std_in, 0) == -1)
		return (perror("miniChell"), 0);
	close(std_in);
	signal_gestionnary();
	return (ongoing);
}

static int	here_document(t_ch *ch, t_token *heredoc, int linex, int fds[2])
{
	const char	found_quote = heredoc->fd;
	char		*line;
	_Bool		found_delimiter;

	heredoc->fd = fds[0];
	found_delimiter = 0;
	line = (char *)1;
	while (line && !found_delimiter)
		line = loop_body(linex++, fds, &found_delimiter, heredoc->str);
	close(fds[1]);
	if (g_signal == SIGINT)
		return (0);
	if (!found_quote)
		return (heredoc_expand(ch, fds[0], &heredoc->fd));
	return (1);
}

static char	*loop_body(int linex, int fds[2], _Bool *found_delim, char *delim)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(0);
	if (g_signal == SIGINT)
		return (ft_free(line));
	if (!line)
	{
		ft_dprintf(2, "miniChell: warning: here-document at line %d deli" \
				"mited by end-of-file (wanted `%s')\n", linex, delim);
		return (NULL);
	}
	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (!trimmed)
		return (perror("miniChell"), NULL);
	*found_delim = !ft_strcmp(trimmed, delim);
	if (*found_delim == 0)
		ft_dprintf(fds[1], "%s\n", trimmed);
	free(trimmed);
	return (trimmed);
}

static void	heredoc_sighandler(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		close(0);
		ch_status_set(130);
		printf("\n");
	}
}
