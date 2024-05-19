/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/18 17:01:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_command *cmd, t_env *env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork in [pipex]");
	else if (pid == 0)
	{
		pipex_forked(cmd, env);
		printf("%d] out of fork\n", pid);
		//ft_free_parray(cmd->path);
		if (cmd->path)
			ft_free(cmd->path[0]);
		cmd->path = ft_free(cmd->path);
		printf("%d] freed path\n", pid);
		ft_free_parray(cmd->penv);
		cmd->penv = NULL;
		printf("%d] freed penv\n", pid);
	}
	else
		waitpid(-1, NULL, 0);
	ft_free_parray(cmd->argv);
	cmd->argv = NULL;
	printf("%d] freed argv\n", pid);
	return (pid >= 0);
}
