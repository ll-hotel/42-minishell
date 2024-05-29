/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:48:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 02:28:46 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_dup2(t_command *cmd)
{
	//ft_dprintf(2, "[%d] %s: < %d    > %d\n", getpid(), cmd->argv[0], cmd->fd_in, cmd->fd_out);
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

int	exec_wait_for_children(t_msh *msh)
{
	uint64_t	i;
	int			status;
	pid_t		may_pid;
	pid_t		*p_child;

	i = 0;
	while (i < msh->children.size)
	{
		p_child = vec_at(&msh->children, i++);
		may_pid = waitpid(*p_child, &status, WNOHANG);
		while (may_pid == 0)
			may_pid = waitpid(*p_child, &status, WNOHANG);
	}
	vec_clear(&msh->children, NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

void	exec_kill_children(t_msh *msh)
{
	uint64_t	i;
	pid_t		child;

	i = 0;
	while (i < msh->children.size)
	{
		child = *(pid_t *)vec_at(&msh->children, i);
		if (kill(child, SIGQUIT) == -1)
			kill(child, SIGKILL);
		i += 1;
	}
	vec_clear(&msh->children, NULL);
}

void	exec_perror_exit(t_msh *msh, int exit_status)
{
	perror("minishell");
	msh_exit(msh, exit_status);
}
