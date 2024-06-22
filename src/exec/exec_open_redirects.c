/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:49:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 20:25:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	open_file(int type, char *filename, int *p_fdin, int *p_fdout);
static int	open_perror(char *filename);

int	exec_open_redirs(t_cmd *cmd)
{
	t_token	*redir;
	int		error;

	error = 0;
	redir = (t_token *)cmd->redirs.first;
	while (redir && !error)
	{
		if (redir->type == TOKEN_HEREDOC)
			error = open_file(redir->type, (char *)(long)redir->fd, \
					&cmd->fd_in, &cmd->fd_out);
		else
			error = open_file(redir->type, redir->str, \
					&cmd->fd_in, &cmd->fd_out);
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
	if (type == TOKEN_REDIR_OUT || type == TOKEN_APPEND)
		ft_close(*p_fdout);
	else
		ft_close(*p_fdin);
	if (type == TOKEN_REDIR_IN)
		*p_fdin = open(filename, O_RDONLY);
	else if (type == TOKEN_HEREDOC)
		*p_fdin = (long)filename;
	else if (type == TOKEN_REDIR_OUT)
		*p_fdout = open(filename, REDIR_OUT_FLAGS, FILE_PERMS);
	else if (type == TOKEN_APPEND)
		*p_fdout = open(filename, APPEND_FLAGS, FILE_PERMS);
	if (type == TOKEN_REDIR_OUT || type == TOKEN_APPEND)
	{
		if (*p_fdout == -1)
			return (open_perror(filename));
	}
	else if (*p_fdin == -1)
		return (open_perror(filename));
	return (0);
}

static int	open_perror(char *filename)
{
	char	*msg;

	msg = ft_strjoin("miniChell: ", filename);
	if (msg)
	{
		perror(msg);
		free(msg);
	}
	else
		perror("miniChell");
	return (1);
}
