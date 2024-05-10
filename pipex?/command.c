/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:43:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/08 12:56:55 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	path_len(char *const path);
static char	*create_executable(char *path, char *call);
static char	*slash_or_empty_path(t_command *cmd);

int	pipex_find_command(char **path, t_command *cmd)
{
	int	i;

	if (!cmd->argv && !cmd->argv[0])
		return (0);
	if (!path || ft_strchr(cmd->argv[0], '/'))
	{
		cmd->executable = slash_or_empty_path(cmd);
		return (cmd->executable != NULL);
	}
	i = -1;
	while (path[++i])
	{
		cmd->executable = create_executable(path[i], cmd->argv[0]);
		if (access(cmd->executable, X_OK) == 0)
			return (1);
		cmd->executable = ft_free(cmd->executable);
	}
	ft_dprintf(2, "pipex: %s: command not found\n", cmd->argv[0]);
	return (0);
}

static char	*slash_or_empty_path(t_command *cmd)
{
	if (!cmd->argv[0][0])
	{
		ft_dprintf(2, "pipex: : command not found\n");
		return (NULL);
	}
	if (access(cmd->argv[0], X_OK) == 0)
		return (cmd->argv[0]);
	pipex_error(cmd->argv[0]);
	return (NULL);
}

static char	*create_executable(char *path, char *call)
{
	const long	pathlen = path_len(path);
	const long	calllen = ft_strlen(call);
	const int	slashed = path[pathlen - 1] == '/';
	char		*executable;

	executable = ft_calloc(calllen + pathlen + !slashed + 1, \
			sizeof(*executable));
	if (executable)
	{
		ft_strlcpy(executable, path, pathlen);
		if (!slashed)
			executable[pathlen] = '/';
		ft_strlcpy(executable, call, calllen);
	}
	return (executable);
}

static int	path_len(char *const path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != ':')
		i += 1;
	return (i);
}
