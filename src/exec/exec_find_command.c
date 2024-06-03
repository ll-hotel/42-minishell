/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:43:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/31 18:00:11 by lrichaud         ###   ########lyon.fr   */
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
		return (!cmd->executable * msh_status_get());
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
	ft_dprintf(2, "\001\e[0m\e[91m\002%s: command not found\n", cmd->argv[0]);
	return (127);
}

static char	*slash_or_empty_path(t_command *cmd)
{
	struct stat	buf;

	if (access(cmd->argv[0], F_OK) == 0)
	{
		if (stat(cmd->argv[0], &buf) != 0)
			return (perror("minishell"), msh_status_set(errno), NULL);
		if (S_ISDIR(buf.st_mode))
		{
			ft_dprintf(2, "\001\e[0m\e[91m\002%s: Is a directory\n", cmd->argv[0]);
			msh_status_set(126);
			return (NULL);
		}
		if (access(cmd->argv[0], X_OK) == 0)
			return (ft_strdup(cmd->argv[0]));
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd->argv[0]);
		msh_status_set(126);
	}
	else
	{
		ft_dprintf(2, "minishell: %s: "\
				"No such file or directory\n", cmd->argv[0]);
		msh_status_set(127);
	}
	return (NULL);
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
