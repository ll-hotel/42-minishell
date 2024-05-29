/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 03:20:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_exec(t_msh *msh, t_command *cmd)
{
	int	pid;
	int	exit_status;

	if (!cmd->next && chooser(cmd, NULL) == 0)
	{
		msh_status_set(chooser(cmd, msh));
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		msh_status_set(errno);
	}
	if (pid == 0)
	{
		if (!cmd->next)
			exit_status = exec_one(msh, cmd);
		else
			exit_status = exec_pipeline(msh, cmd);
		msh_exit(msh, exit_status);
	}
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		msh_status_set(WEXITSTATUS(exit_status));
}
