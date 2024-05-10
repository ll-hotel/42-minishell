/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:39:40 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/08 10:02:26 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

static int	measure_path_len(char *path);
static int	next_subpath(char *path);

char	**pipex_get_path(t_env *env)
{
	void	*path;
	char	**paths;
	int		path_len;
	int		i;
	int		tmp;

	path = env_var_get(env, "PATH");
	if (!path || !((t_env_var *)path)->value)
		return (NULL);
	path = ((t_env_var *)path)->value;
	path_len = measure_path_len(path);
	paths = ft_calloc(path_len + 1, sizeof(char *));
	if (!paths)
		return (pipex_error("ft_calloc in ft_get_path"), NULL);
	i = -1;
	tmp = next_subpath(path);
	while (++i < path_len)
	{
		paths[i] = path + tmp;
		((char *)path)[tmp] = 0;
		tmp = next_subpath(path + tmp);
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
