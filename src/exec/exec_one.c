/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:25:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 05:16:20 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one(t_msh *msh, t_command *cmd)
{
	int	status;

	cmd->envp = env_to_array((t_env_var *)msh->env_vars.first);
	cmd->path = exec_get_path(msh);
	if (exec_open_redirections(cmd) != 0)
		return (errno);
	status = exec_find_command(cmd, cmd->path);
	if (status != 0)
	{
		ft_close(cmd->fd_in);
		ft_close(cmd->fd_out);
		msh_exit(msh, status);
	}
	if (exec_dup2(cmd) != 0)
		return (errno);
	return (execve(cmd->executable, cmd->argv, cmd->envp));
}
