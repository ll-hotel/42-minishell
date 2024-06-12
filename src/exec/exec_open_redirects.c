/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:49:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/12 22:49:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(int type, char *filename, int *p_fdin, int *p_fdout);
static int	open_perror(char *filename);

int	exec_open_redirects(t_command *cmd)
{
	t_token	*redir;
	int		error;

	error = 0;
	redir = (t_token *)cmd->redirects.first;
	while (redir && !error)
	{
		if (redir->type == TOKEN_HEREDOC)
			error = open_file(redir->type, (char *)(long)redir->fd, \
					&cmd->fd_in, &cmd->fd_out) == -1;
		else
			error = open_file(redir->type, redir->str, \
					&cmd->fd_in, &cmd->fd_out) == -1;
		redir = redir->next;
	}
	if (error)
	{
		cmd->fd_in = ft_close(cmd->fd_in);
		cmd->fd_out = ft_close(cmd->fd_out);
	}
	return (error);
}

static int	open_file(int type, char *filename, int *p_fdin, int *p_fdout)
{
	int	oldin;
	int	oldout;

	oldin = *p_fdin;
	oldout = *p_fdout;
	if (type == TOKEN_REDIR_OUT || type == TOKEN_APPEND)
		ft_close(oldout);
	else
		ft_close(oldin);
	if (type == TOKEN_REDIR_IN)
		*p_fdin = open(filename, O_RDONLY);
	else if (type == TOKEN_REDIR_OUT)
		*p_fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == TOKEN_APPEND)
		*p_fdout = open(filename, O_CREAT | O_WRONLY | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == TOKEN_HEREDOC)
		*p_fdin = (long)filename;
	if ((type == TOKEN_REDIR_OUT || type == TOKEN_APPEND) \
			&& oldout >= 0 && *p_fdout == -1)
		return (open_perror(filename));
	else if (oldin >= 0 && *p_fdin == -1)
		return (open_perror(filename));
	return (0);
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
