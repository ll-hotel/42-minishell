/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:28:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 22:09:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	mini_pipe(t_ch *ch, t_cmd *cmd, int fd_pipe[2]);
static void	mini_chooser(t_ch *ch, t_cmd *cmd);
static void	mini_sighandler(int signal);

int	exec_pipeline(t_ch *ch)
{
	t_cmd	*cmd;
	int		pid;
	int		fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	signal(SIGINT, mini_sighandler);
	while (ch->cmds.first)
	{
		cmd = (t_cmd *)ch->cmds.first;
		if (cmd->next)
			mini_pipe(ch, cmd, fd_pipe);
		pid = fork();
		if (pid == -1)
			exec_perror_exit(ch, errno);
		else if (pid == 0)
			mini_chooser(ch, cmd);
		ft_close(fd_pipe[1]);
		llst_delone(&ch->cmds, cmd_free);
	}
	return (exec_wait_children(pid));
}

static void	mini_pipe(t_ch *ch, t_cmd *cmd, int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		exec_perror_exit(ch, 1);
	cmd->fd_out = fd_pipe[1];
	cmd->next->fd_in = fd_pipe[0];
}

static void	mini_chooser(t_ch *ch, t_cmd *cmd)
{
	int	status;

	status = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (chooser(cmd, NULL) == 0)
		status = chooser(cmd, ch);
	else
	{
		if (cmd->next)
			cmd->next->fd_in = ft_close(cmd->next->fd_in);
		exec_one(ch, cmd);
	}
	ch_exit(ch, status);
}

static void	mini_sighandler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ch_status_set(130);
	}
}
