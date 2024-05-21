/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/21 13:33:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_command *cmd, t_env *env)
{
	int	pid;
	int	child_status;

	child_status = 0;
	pid = fork();
	if (pid == -1)
		perror("minishell");
	else if (pid == 0)
		pipex_forked(cmd, env);
	else
		waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		return (WEXITSTATUS(child_status));
	return (-1);
}
