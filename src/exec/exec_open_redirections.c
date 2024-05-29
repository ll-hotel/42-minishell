/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:49:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 15:16:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redirection_in(char *filename, int last_fd);
static int	open_redirection_out(char *filename, int last_fd);
static int	open_perror(char *filename);

int	exec_open_redirections(t_command *cmd)
{
	t_token	*redirection;
	int		last_in;
	int		last_out;
	int		error;

	last_in = cmd->fd_in;
	last_out = cmd->fd_out;
	error = 0;
	redirection = (t_token *)cmd->redirections.first;
	while (redirection && !error)
	{
		if (redirection->type == TOKEN_REDIR_IN)
			last_in = open_redirection_in(redirection->str, last_in);
		else
			last_out = open_redirection_out(redirection->str, last_out);
		if (last_in == -1 && last_out == -1)
			error = 1;
		redirection = redirection->next;
	}
	if (last_in > 0)
		cmd->fd_in = last_in;
	if (last_out > 1)
		cmd->fd_out = last_out;
	return (error);
}

static int	open_redirection_in(char *filename, int last_fd)
{
	int	fd;

	ft_close(last_fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (open_perror(filename));
	return (fd);
}

static int	open_redirection_out(char *filename, int last_fd)
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
