/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:43:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/18 00:36:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_path_len(char *const path);
static char	*ft_assemble_command(char *const path, const char *call);
static char	**ft_wrap_command(char *call, char **const command);
static char	**check_slash_or_empty_command(char **cmd_args, char *cmd, \
		char **path);

char	**ft_find_command(char **path, char *cmd)
{
	char	*call;
	char	*slash;
	char	**cmd_args;
	int		i;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		return (ft_error("ft_split failed"), NULL);
	if (!cmd_args[0])
		cmd_args = check_slash_or_empty_command(cmd_args, cmd, path);
	if (!cmd_args)
		return (NULL);
	slash = ft_strchr(cmd_args[0], '/');
	if (!path || slash)
		return (check_slash_or_empty_command(cmd_args, NULL, NULL));
	i = -1;
	while (path[++i])
	{
		call = ft_assemble_command(path[i], cmd_args[0]);
		if (access(call, X_OK) == 0)
			return (ft_wrap_command(call, cmd_args));
		free(call);
	}
	return (ft_dprintf(2, "pipex: %s: command not found\n", cmd), \
			ft_free_parray((void **)cmd_args), free(cmd_args), NULL);
}

static char	**check_slash_or_empty_command(char **cmd_args, char *cmd, \
		char **path)
{
	if (cmd_args && cmd_args[0])
	{
		if (access(cmd_args[0], X_OK) == 0)
			return (ft_wrap_command(cmd_args[0], cmd_args));
		return (ft_error(cmd_args[0]), \
				ft_free_parray((void **)cmd_args), free(cmd_args), NULL);
	}
	if (!cmd)
		return (NULL);
	if (!cmd[0])
	{
		if (path)
			return (ft_dprintf(2, "pipex: %s: command not found\n", cmd), \
					free(cmd_args), NULL);
		return (access(cmd, X_OK), ft_error(cmd), free(cmd_args), NULL);
	}
	cmd_args = ft_realloc(cmd_args, sizeof(char *), 2 * sizeof(char *));
	if (!cmd_args)
		return (ft_error("ft_realloc failed"), NULL);
	cmd_args[0] = ft_strdup(cmd);
	if (!cmd_args[0])
		return (ft_error("ft_strdup failed"), NULL);
	cmd_args[1] = 0;
	return (cmd_args);
}

static char	*ft_assemble_command(char *const path, const char *call)
{
	const int	path_len = ft_path_len(path);
	char		*tmp;
	char		*command;

	command = ft_strdup(path);
	if (path_len && path[path_len - 1] != '/')
	{
		tmp = command;
		command = ft_strjoin(tmp, "/");
		free(tmp);
	}
	tmp = command;
	command = ft_strjoin(tmp, call);
	free(tmp);
	return (command);
}

static int	ft_path_len(char *const path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != ':')
		i += 1;
	return (i);
}

static char	**ft_wrap_command(char *call, char **const command)
{
	char	**wrapped;
	int		l;

	l = 0;
	while (command[l])
		l += 1;
	wrapped = malloc(sizeof(char *) * (l + 2));
	if (!wrapped)
		return (NULL);
	wrapped[0] = call;
	l = 0;
	while (command[++l])
		wrapped[l] = command[l];
	wrapped[l] = NULL;
	return (free(command), wrapped);
}
