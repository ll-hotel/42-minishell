/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:48:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 02:55:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static int	sig_return_value(int signal);

int	exec_dup2(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			return (perror("miniChell: fd_in dup2"), 1);
		cmd->fd_in = ft_close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			return (perror("miniChell: fd_out dup2"), 1);
		cmd->fd_out = ft_close(cmd->fd_out);
	}
	return (0);
}

void	exec_perror_exit(t_ch *ch, int exit_status)
{
	perror("miniChell");
	ch_exit(ch, exit_status);
}

int	exec_wait_children(int last_pid)
{
	pid_t	pid;
	int		old_status;
	int		status;
	int		newline;

	old_status = 0x0100;
	pid = waitpid(-1, &status, 0);
	newline = 0;
	while (pid > 0)
	{
		if (pid == last_pid)
			old_status = status;
		pid = waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			newline = 1;
	}
	if (newline)
		ft_putstr_fd("\n", 2);
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
	if (signal == SIGINT)
	{
		return (130);
	}
	return (1);
}
