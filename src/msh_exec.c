/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 19:37:43 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec(t_msh *msh, t_command *cmd)
{
	int	pid;
	int	exit_status;

	if (!cmd->next && chooser(cmd, NULL) == 0)
		return (chooser(cmd, msh));
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (EXIT_OUT_OF_MEMORY);
	}
	if (pid == 0)
	{
		if (!cmd->next)
			exit_status = msh_exec_one(msh, cmd);
		else
			exit_status = msh_exec_pipeline(msh, cmd);
		msh_exit(msh, exit_status);
	}
	else
		waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (exit_status);
}
