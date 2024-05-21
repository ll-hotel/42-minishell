/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:39:40 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/21 13:07:36 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	measure_path_len(char *path);
static int	next_subpath(char *path);

char	**pipex_get_path(t_env *env)
{
	char	*path;
	char	**paths;
	int		path_len;
	int		i;
	int		tmp;

	path = (char *)env_var_get(env, "PATH");
	if (!path || !((t_env_var *)path)->value)
		return (NULL);
	path = ft_strdup(((t_env_var *)path)->value);
	if (!path)
		return (NULL);
	path_len = measure_path_len(path);
	paths = ft_calloc(path_len + 1, sizeof(*paths));
	if (!paths)
		return (pipex_error("ft_calloc in ft_get_path"), NULL);
	i = -1;
	tmp = 0;
	while (++i < path_len)
	{
		paths[i] = path;
		tmp = next_subpath(path);
		((char *)path)[tmp] = 0;
		path += tmp + 1;
	}
	return (paths);
}

static int	measure_path_len(char *path)
{
	int	i;

	i = 1;
	while (*path)
		i += *(path++) == ':';
	return (i);
}

static int	next_subpath(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != ':')
		i += 1;
	return (i);
}
