/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:28:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 15:52:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	msh_exec_perror_exit(t_msh *msh, int exit_status);

int	msh_exec_pipeline(t_msh *msh, t_command *cmd)
{
	int	pid;
	int	fd_pipe[2];

	if (cmd->next)
	{
		if (pipe(fd_pipe) == -1)
			msh_exec_perror_exit(msh, EXIT_BROKEN_PIPE);
		cmd->fd_out = fd_pipe[1];
		cmd->next->fd_in = fd_pipe[0];
		pid = fork();
		if (pid == -1)
		{
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			msh_exec_perror_exit(msh, EXIT_OUT_OF_MEMORY);
		}
		else if (pid == 0)
			return (msh_exec_pipeline(msh, cmd->next));
		close(fd_pipe[0]);
	}
	if (chooser(cmd, NULL) == 0)
		pid = chooser(cmd, msh);
	else
		pid = msh_exec_one(cmd, &msh->env);
	return (pid);
}

static void	msh_exec_perror_exit(t_msh *msh, int exit_status)
{
	perror("minishell");
	msh_exit(msh, exit_status);
}
