/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:43:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 13:03:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_executable(char *dir, char *program);
static char	*slash_or_empty_path(t_command *cmd);

int	exec_find_command(t_command *cmd, char **path)
{
	int	i;

	if (!cmd->argv || !cmd->argv[0])
		return (1);
	if (!path || ft_strchr(cmd->argv[0], '/'))
	{
		cmd->executable = slash_or_empty_path(cmd);
		return (cmd->executable == NULL);
	}
	if (cmd->argv[0][0])
	{
		i = -1;
		while (path[++i])
		{
			cmd->executable = create_executable(path[i], cmd->argv[0]);
			if (access(cmd->executable, X_OK) == 0)
				return (0);
			cmd->executable = ft_free(cmd->executable);
		}
	}
	ft_dprintf(2, "minishell: %s: command not found\n", cmd->argv[0]);
	return (1);
}

static char	*slash_or_empty_path(t_command *cmd)
{
	char	*msg;

	if (access(cmd->argv[0], X_OK) == 0)
		return (ft_strdup(cmd->argv[0]));
	msg = ft_strjoin("minishell:", cmd->argv[0]);
	if (msg)
		perror(msg);
	else
		perror("minishell:");
	return (ft_free(msg));
}

static char	*create_executable(char *dir, char *program)
{
	const long	dir_len = ft_strlen(dir);
	const long	program_len = ft_strlen(program);
	const int	slashed = dir[dir_len - 1] == '/';
	const long	executable_len = dir_len + program_len + !slashed;
	char		*executable;

	executable = ft_calloc(executable_len + 1, sizeof(*executable));
	if (executable)
	{
		ft_strlcpy(executable, dir, executable_len + 1);
		if (!slashed)
			executable[dir_len] = '/';
		ft_strlcat(executable, program, executable_len + 1);
	}
	return (executable);
}
