/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:49:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/31 18:00:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redirect_in(char *filename, int last_fd);
static int	open_redirect_out(char *filename, int last_fd);
static int	open_perror(char *filename);

int	exec_open_redirects(t_command *cmd)
{
	t_token	*redirect;
	int		error;

	error = 0;
	redirect = (t_token *)cmd->redirects.first;
	while (redirect && !error)
	{
		if (redirect->type == TOKEN_REDIR_IN)
			cmd->fd_in = open_redirect_in(redirect->str, cmd->fd_in);
		else if (redirect->type == TOKEN_REDIR_OUT)
			cmd->fd_out = open_redirect_out(redirect->str, cmd->fd_out);
		if (cmd->fd_in == -1 && cmd->fd_out == -1)
			error = 1;
		redirect = redirect->next;
	}
	return (error);
}

static int	open_redirect_in(char *filename, int last_fd)
{
	int	fd;

	ft_close(last_fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (open_perror(filename));
	return (fd);
}

static int	open_redirect_out(char *filename, int last_fd)
{
	int	fd;

	ft_close(last_fd);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (open_perror(filename));
	return (fd);
}

static int	open_perror(char *filename)
{
	char	*msg;

	msg = ft_strjoin("minishell: ", filename);
	if (msg)
	{
		perror(msg);
		free(msg);
	}
	else
		perror("minishell");
	return (-1);
}
