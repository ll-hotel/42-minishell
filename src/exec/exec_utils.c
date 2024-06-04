/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:48:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/03 06:35:03 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	exec_dup2(t_command *cmd)
{
	if (cmd->fd_in > 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			return (perror("minishell: fd_in dup2"), 1);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			return (perror("minishell: fd_out dup2"), 1);
		close(cmd->fd_out);
	}
	return (0);
}

void	exec_perror_exit(t_msh *msh, int exit_status)
{
	perror("minishell");
	msh_exit(msh, exit_status);
}

int	exec_wait_children(void)
{
	pid_t	pid;
	int		old_status;
	int		status;

	old_status = 0x0100;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		old_status = status;
		pid = waitpid(-1, &status, 0);
	}
	if (WIFEXITED(old_status))
		return (WEXITSTATUS(old_status));
	return (1);
}
