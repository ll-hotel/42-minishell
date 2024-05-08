/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:39:40 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/20 19:52:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_getenv_var(char *const penv[], const char *var);
static int	ft_measure_path_len(char *path);
int			ft_next_subpath(char *path);

char	**ft_get_path(char **penv)
{
	char	*path;
	char	**paths;
	int		path_len;
	int		i;
	int		tmp;

	path = ft_getenv_var(penv, "PATH");
	if (!path || !path[5])
		return (NULL);
	path = ft_strdup(path + 5);
	if (!path)
		return (ft_error("ft_strdup in path"), NULL);
	path_len = ft_measure_path_len(path);
	paths = ft_calloc(path_len + 1, sizeof(char *));
	if (!paths)
		return (ft_error("ft_calloc in ft_get_path"), NULL);
	i = -1;
	while (++i < path_len)
	{
		paths[i] = path;
		tmp = ft_next_subpath(path);
		path[tmp] = 0;
		path += tmp + 1;
	}
	return (paths);
}

static char	*ft_getenv_var(char *const penv[], const char *var)
{
	const int		var_len = ft_strlen(var);
	unsigned int	i;

	if (!penv)
		return (NULL);
	i = 0;
	while (penv[i] && ft_strncmp(penv[i], var, var_len))
		i += 1;
	return (penv[i]);
}

static int	ft_measure_path_len(char *path)
{
	int	i;

	i = 1;
	while (*path)
		i += *(path++) == ':';
	return (i);
}

int	ft_next_subpath(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != ':')
		i += 1;
	return (i);
}
