/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:10:45 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/20 01:53:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	select_builtin(t_ch *ch, t_cmd *cmd);
static int	is_not_builtin(char *cmd);
static int	dup_fds(int *old_in, int *old_out, int saving);

int	chooser(t_cmd *cmd, t_ch *ch)
{
	int	old_in;
	int	old_out;
	int	status;

	if (cmd->argc < 1)
		return (-1);
	if (!ch)
		return (is_not_builtin(cmd->argv[0]));
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (exit_error_checker(ch, cmd));
	dup_fds(&old_in, &old_out, 1);
	if (exec_open_redirs(cmd))
	{
		dup_fds(&old_in, &old_out, 0);
		return (1);
	}
	status = select_builtin(ch, cmd);
	dup_fds(&old_in, &old_out, 0);
	return (status);
}

static int	select_builtin(t_ch *ch, t_cmd *cmd)
{
	int	status;

	if (exec_dup2(cmd) != 0)
		return (1);
	status = -1;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		status = ch_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		status = ch_env(cmd, ch);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		status = ch_cd(cmd, ch);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		status = ch_pwd(ch);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		status = ch_export(cmd, ch);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		status = ch_unset(cmd, ch);
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
			perror("miniChell");
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
		perror("miniChell");
		return (1);
	}
	return (0);
}

static int	is_not_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") && \
			ft_strcmp(cmd, "env") && \
			ft_strcmp(cmd, "cd") && \
			ft_strcmp(cmd, "pwd") && \
			ft_strcmp(cmd, "export") && \
			ft_strcmp(cmd, "unset") && \
			ft_strcmp(cmd, "exit"));
}
