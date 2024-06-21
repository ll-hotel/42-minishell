/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/21 15:39:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"
#include <sys/ioctl.h>

//static void	heredoc_sighandler(int signal);
static int	here_document(t_ch *ch, t_token *heredoc, int linex, int fds[2]);
static int	quit_here_document(char *line, int fd[2]);

int	parser_heredoc(t_token *head, t_ch *ch)
{
	int		fds[2];
	int		ongoing;

	int std_in = dup(0);
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
	dup2(std_in, 0);
	return (ongoing);
}

static int	here_document(t_ch *ch, t_token *heredoc, int linex, int fds[2])
{
	const char	found_quote = heredoc->fd;
	char		*line;
	int			found_delimiter;

	found_delimiter = 0;
	while (!found_delimiter)
	{
		line = readline("> ");
		if (line && ft_strcmp(line, heredoc->str))
			ft_dprintf(fds[1], "%s\n", line);
		if (!line)
		{
			ft_dprintf(2, "miniChell: warning: here-document at line %d deli" \
				"mited by end-of-file (wanted `%s')\n", linex, heredoc->str);
			return (quit_here_document(NULL, fds));
		}
		found_delimiter = (++linex && !ft_strcmp(line, heredoc->str));
		free(line);
	}
	close(fds[1]);
	if (!line)
		return (0);
	heredoc->fd = fds[0];
	if (!found_quote)
		return (heredoc_expand(ch, fds[0], &heredoc->fd));
	return (1);
}

static int	quit_here_document(char *line, int fd[2])
{
	ft_free(line);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

// static void	heredoc_sighandler(int signal)
// {
// 	g_signal = signal;
// 	if (signal == SIGINT)
// 	{
// 		ch_status_set(130);
// 		ioctl(0, TIOCSIG, "\n");
// 	}
// }
