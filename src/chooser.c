/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:10:45 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/22 20:20:21 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_not_builtin(char *command);

int	chooser(t_command *cmd, t_msh *msh)
{
	if (cmd->argc < 1)
		return (-1);
	if (!msh)
		return (is_not_builtin(cmd->argv[0]));
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (msh_echo(cmd));
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (msh_cd(cmd, &msh->env));
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (msh_pwd(cmd));
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (msh_env(cmd, &msh->env));
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (msh_export(cmd, &msh->env));
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (msh_unset(cmd, &msh->env));
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		msh_exit(msh, 0);
	return (-1);
}

static int	is_not_builtin(char *command)
{
	return (ft_strncmp(command, "echo", 5) && \
			ft_strncmp(command, "cd", 3) && \
			ft_strncmp(command, "pwd", 4) && \
			ft_strncmp(command, "env", 4) && \
			ft_strncmp(command, "export", 7) && \
			ft_strncmp(command, "unset", 6) && \
			ft_strncmp(command, "exit", 5));
}
