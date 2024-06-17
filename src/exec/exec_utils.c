/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:48:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 13:50:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	sig_return_value(int signal);

int	exec_dup2(t_command *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			return (perror("minishell: fd_in dup2"), 1);
		cmd->fd_in = ft_close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			return (perror("minishell: fd_out dup2"), 1);
		cmd->fd_out = ft_close(cmd->fd_out);
	}
	return (0);
}

void	exec_perror_exit(t_msh *msh, int exit_status)
{
	perror("minishell");
	msh_exit(msh, exit_status);
}

int	exec_wait_children(int last_pid)
{
	pid_t	pid;
	int		old_status;
	int		status;

	old_status = 0x0100;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
			old_status = status;
		pid = waitpid(-1, &status, 0);
	}
	if (WIFSIGNALED(old_status))
		return (sig_return_value(WTERMSIG(old_status)));
	if (WIFEXITED(old_status))
		return (WEXITSTATUS(old_status));
	return (1);
}

static int	sig_return_value(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (131);
	}
	return (1);
}
