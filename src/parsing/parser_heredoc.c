/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/06 16:15:01 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sighandler(int sig);
static int	here_fork(t_msh *msh, int fd_pipe[2], char *delimiter);
static void	heredocking(int fd, char *delimiter);
static void	update_str(char *delimiter, char **str, int *len, int *delfound);

int	parser_heredoc(t_token *head, t_msh *msh)
{
	int	fd_pipe[2];

	while (head && head->next)
	{
		while (head->next && head->next->type != TOKEN_HEREDOC)
			head = head->next;
		if (!head->next)
			continue ;
		if (pipe(fd_pipe) == -1)
		{
			perror("here-document");
			return (0);
		}
		here_fork(msh, fd_pipe, head->next->str);
		head->next->str = ft_free(head->next->str);
		head->next->fd = fd_pipe[0];
		head = head->next;
	}
	return (1);
}

static int	here_fork(t_msh *msh, int fd_pipe[2], char *delimiter)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("here-document");
		return (0);
	}
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		signal(SIGINT, heredoc_sighandler);
		heredocking(fd_pipe[1], delimiter);
		msh_exit(msh, 0);
	}
	close(fd_pipe[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		msh_status_set(WEXITSTATUS(status));
	return (0);
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
	if (!delimiter_found && msh_status_get() != 130)
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

static void	heredoc_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		msh_status_set(130);
	}
}
