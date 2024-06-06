/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:28:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/06 15:35:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mini_pipe(t_msh *msh, t_command *cmd, int fd_pipe[2]);
static void	mini_chooser(t_msh *msh, t_command *cmd);

int	exec_pipeline(t_msh *msh)
{
	t_command	*cmd;
	int			pid;
	int			fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	while (msh->cmds.first)
	{
		cmd = (t_command *)msh->cmds.first;
		if (cmd->next)
			mini_pipe(msh, cmd, fd_pipe);
		pid = fork();
		if (pid == -1)
			exec_perror_exit(msh, errno);
		else if (pid == 0)
			mini_chooser(msh, cmd);
		ft_close(fd_pipe[1]);
		llst_delone(&msh->cmds, command_free);
	}
	return (exec_wait_children());
}

static void	mini_pipe(t_msh *msh, t_command *cmd, int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		exec_perror_exit(msh, 1);
	cmd->fd_out = fd_pipe[1];
	cmd->next->fd_in = fd_pipe[0];
}

static void	mini_chooser(t_msh *msh, t_command *cmd)
{
	int	status;

	status = 1;
	if (chooser(cmd, NULL) == 0)
		status = chooser(cmd, msh);
	else
	{
		if (cmd->next)
			cmd->next->fd_in = ft_close(cmd->next->fd_in);
		exec_one(msh, cmd);
	}
	msh_exit(msh, status);
}
