/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:10:45 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/17 22:03:37 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

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
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		status = ch_echo(cmd);
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		status = ch_cd(cmd, ch);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		status = ch_pwd(ch);
	else if (!ft_strncmp(cmd->argv[0], "ch", 4))
		status = ch_env(cmd, ch);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		status = ch_export(cmd, ch);
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
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
	return (ft_strncmp(cmd, "echo", 5) && \
			ft_strncmp(cmd, "cd", 3) && \
			ft_strncmp(cmd, "pwd", 4) && \
			ft_strncmp(cmd, "ch", 4) && \
			ft_strncmp(cmd, "export", 7) && \
			ft_strncmp(cmd, "unset", 6) && \
			ft_strncmp(cmd, "exit", 5));
}
