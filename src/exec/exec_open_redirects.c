/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:49:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/04 19:16:00 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_in(char *filename, int *p_fd);
static int	open_out(char *filename, int *p_fd);
static int	open_append(char *filename, int *p_fd);
static int	open_perror(char *filename);

int	exec_open_redirects(t_command *cmd)
{
	t_token	*redirect;
	int		error;

	error = 0;
	redirect = (t_token *)cmd->redirects.first;
	while (redirect && !error)
	{
		if (redirect->type == TOKEN_REDIR_IN && \
				open_in(redirect->str, &cmd->fd_in) == -1)
			cmd->fd_out = ft_close(cmd->fd_out);
		else if (redirect->type == TOKEN_REDIR_OUT && \
				open_out(redirect->str, &cmd->fd_out) == -1)
			cmd->fd_in = ft_close(cmd->fd_in);
		else if (redirect->type == TOKEN_APPEND && \
				open_append(redirect->str, &cmd->fd_out) == -1)
			cmd->fd_in = ft_close(cmd->fd_in);
		if (cmd->fd_in == -1 && cmd->fd_out == -1)
			error = 1;
		redirect = redirect->next;
	}
	return (error);
}

static int	open_in(char *filename, int *p_fd)
{
	ft_close(*p_fd);
	*p_fd = open(filename, O_RDONLY);
	if (*p_fd == -1)
		return (open_perror(filename));
	return (*p_fd);
}

static int	open_out(char *filename, int *p_fd)
{
	ft_close(*p_fd);
	*p_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*p_fd == -1)
		return (open_perror(filename));
	return (*p_fd);
}

static int	open_append(char *filename, int *p_fd)
{
	ft_close(*p_fd);
	*p_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*p_fd == -1)
		return (open_perror(filename));
	return (*p_fd);
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
