/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/20 18:28:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	heredoc_sighandler(int signal);
static int	empty_fun(void);
static int	here_document(t_ch *ch, t_token *heredoc, int linex, int fds[2]);
static int	quit_here_document(char *line, int fd[2]);

int	parser_heredoc(t_token *head, t_ch *ch)
{
	int		fds[2];
	int		ongoing;
	void	*event;

	signal(SIGINT, heredoc_sighandler);
	int std_in = dup(0);
	// event = rl_event_hook;
	// rl_event_hook = empty_fun;
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
	// rl_event_hook = event;
	dup2(std_in, 0);
	signal_gestionnary();
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
		rl_done = 0;
		if (g_signal == SIGINT)
			return (quit_here_document(line, fds));
		if (!line)
		{
			ft_dprintf(2, "miniChell: warning: here-document at line %d deli" \
				"mited by end-of-file (wanted `%s')\n", linex, heredoc->str);
			return (quit_here_document(NULL, fds));
		}
		ft_dprintf(2, "Connard de fdp de readline de ses morts\n");
		found_delimiter = (++linex && !ft_strcmp(line, heredoc->str));
		ft_dprintf(fds[1], "%s\n", line);
		free(line);
	}
	close(fds[1]);
	heredoc->fd = fds[0];
	if (!found_quote)
		return (heredoc_expand(ch, fds[0], &heredoc->fd));
	return (1);
}

static int	empty_fun(void)
{
	return (0);
}

static int	quit_here_document(char *line, int fd[2])
{
	ft_free(line);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

static void	heredoc_sighandler(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ch_status_set(130);
		// rl_done = 1;
		close(0);
	}
}

