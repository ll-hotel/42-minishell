/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:10:45 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/06 16:38:42 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	select_builtin(t_msh *msh, t_command *cmd);
static int	is_not_builtin(char *command);
static int	dup_fds(int *old_in, int *old_out, int saving);

int	chooser(t_command *cmd, t_msh *msh)
{
	int	old_in;
	int	old_out;
	int	status;

	if (cmd->argc < 1)
		return (-1);
	if (!msh)
		return (is_not_builtin(cmd->argv[0]));
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		exit_error_checker(msh, cmd);
	dup_fds(&old_in, &old_out, 1);
	if (exec_open_redirects(cmd))
	{
		dup_fds(&old_in, &old_out, 0);
		return (1);
	}
	status = select_builtin(msh, cmd);
	dup_fds(&old_in, &old_out, 0);
	return (status);
}

static int	select_builtin(t_msh *msh, t_command *cmd)
{
	int	status;

	if (exec_dup2(cmd) != 0)
		return (1);
	status = -1;
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		status = msh_echo(cmd);
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		status = msh_cd(cmd, msh);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		status = msh_pwd();
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		status = msh_env(cmd, msh);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		status = msh_export(cmd, msh);
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		status = msh_unset(cmd, msh);
	return (status);
}

static int	dup_fds(int *old_in, int *old_out, int saving)
{
	if (saving)
	{
		*old_in = dup(0);
		*old_out = dup(1);
		if (*old_in == -1 || *old_out == -1)
		{
			perror("minishell");
			ft_close(*old_in);
			ft_close(*old_out);
			return (1);
		}
	}
	else if (dup2(*old_in, 0) == -1 || \
			dup2(*old_out, 1) == -1 || \
			close(*old_in) || \
			close(*old_out))
	{
		perror("minishell");
		return (1);
	}
	return (0);
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
