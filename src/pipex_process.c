/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:30:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/18 16:15:49 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_exec(t_command *cmd, char **path, int fd_in, int fd_out)
{
	pipex_find_command(cmd, path);
	if (!cmd->executable || dup2(fd_in, 0) == -1 || dup2(fd_out, 1) == -1)
	{
		pipex_close_fds(0, fd_in, fd_out);
		return (1);
	}
	pipex_close_fds(0, fd_in, fd_out);
	return (execve(cmd->executable, cmd->argv, cmd->penv));
}

int	pipex_child(t_command *cmd, char **path, int fd_in, int fd_out)
{
	int	pip[2];
	int	pid2;

	if (!cmd)
		return (pipex_close_fds(1, fd_in, fd_out), 1);
	if (!cmd->next)
		return (pipex_exec(cmd, path, fd_in, fd_out));
	if (pipe(pip) == -1)
		return (pipex_error("pipe"));
	pid2 = fork();
	if (pid2 == -1)
	{
		pipex_close_fds(0, pip[0], pip[1]);
		pipex_close_fds(0, fd_in, fd_out);
		pipex_error("fork in child");
		return (1);
	}
	else if (pid2)
	{
		pipex_close_fds(0, pip[0], fd_out);
		return (pipex_exec(cmd, path, fd_in, pip[1]));
	}
	pipex_close_fds(0, pip[1], fd_in);
	return (pipex_child(cmd->next, path, pip[0], fd_out));
}
