/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:10:45 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/31 15:40:29 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_not_builtin(char *command);
static int	ft_is_number(char *str);
static void	exit_error_checker(t_msh *msh, t_command *cmd);

int	chooser(t_command *cmd, t_msh *msh)
{
	if (cmd->argc < 1)
		return (-1);
	if (!msh)
		return (is_not_builtin(cmd->argv[0]));
	if (exec_dup2(cmd) != 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (msh_echo(cmd));
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (msh_cd(cmd, msh));
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (msh_pwd());
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (msh_env(cmd, msh));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (msh_export(cmd, msh));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (msh_unset(cmd, msh));
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		exit_error_checker(msh, cmd);
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

static int	ft_is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '\0')
			return (0);
		if (!ft_isdigit(str[i]))
		{
			if (str[i] != '-' && str[i] != '+')
				return (0);
			if (str[i + 1] == '\0')
				return (0);
			if (i >= 1 && str[i - 1] != ' ')
				return (0);
		}
		i++;
	}
	return (1);
}

static void	exit_error_checker(t_msh *msh, t_command *cmd)
{
	if (cmd->argc > 2)
	{
		write(2, " too many arguments\n", 20);
		msh_exit(msh, 1);
	}
	if (cmd->argv[1] && !ft_is_number(cmd->argv[1]))
	{
		write(2, " numeric argument required\n", 27);
		msh_exit(msh, 2);
		return ;
	}
	msh_exit(msh, ft_atoi(cmd->argv[1]));
}
