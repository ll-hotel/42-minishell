/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:39:40 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/22 19:20:15 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static int	count_path_nb(char *path);
static int	next_subpath(char *path);
static void	fill_paths(char **paths, char *path, int path_nb);

char	**exec_get_path(t_ch *ch)
{
	void	*path;
	char	**paths;
	int		path_nb;

	path = (char *)evar_get(ch, "PATH");
	if (!path || !((t_evar *)path)->value)
		return (NULL);
	path = ft_strdup(((t_evar *)path)->value);
	if (!path)
		return (NULL);
	path_nb = count_path_nb(path);
	paths = ft_calloc(path_nb + 1, sizeof(*paths));
	if (!paths)
		return (perror("miniChell:"), NULL);
	fill_paths(paths, path, path_nb);
	return (paths);
}

static void	fill_paths(char **paths, char *path, int path_nb)
{
	int	tmp;
	int	i;

	i = -1;
	tmp = 0;
	while (++i < path_nb)
	{
		paths[i] = path;
		tmp = next_subpath(path);
		((char *)path)[tmp] = 0;
		path += tmp + 1;
	}
}

static int	count_path_nb(char *path)
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
