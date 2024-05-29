/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:25:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 02:39:50 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec_one(t_msh *msh, t_command *cmd)
{
	cmd->envp = env_to_array(&msh->env);
	cmd->path = msh_exec_get_path(&msh->env);
	if (msh_exec_open_redirections(cmd) != 0)
		return (errno);
	if (msh_exec_find_command(cmd, cmd->path) == 1)
	{
		ft_close(cmd->fd_in);
		ft_close(cmd->fd_out);
		msh_exit(msh, EXIT_CMD_NOT_FOUND);
	}
	if (exec_dup2(cmd) != 0)
		return (errno);
	return (execve(cmd->executable, cmd->argv, cmd->envp));
}
