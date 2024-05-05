/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:25:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 15:48:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec_one(t_command *cmd, t_env *env)
{
	cmd->envp = env_to_array(env);
	cmd->path = msh_exec_get_path(env);
	if (msh_exec_open_redirections(cmd) != 0)
		return (1);
	if (msh_exec_find_command(cmd, cmd->path) == 1)
	{
		ft_close(cmd->fd_in);
		ft_close(cmd->fd_out);
		return (EXIT_CMD_NOT_FOUND);
	}
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
	return (execve(cmd->executable, cmd->argv, cmd->envp));
}
