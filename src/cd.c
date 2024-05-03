/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:43:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/03 16:16:00 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	char	*home;
	size_t	i;

	if (!ft_strncmp(path, "cd", 2))
	{
		i = 2;
		while (path[i] && is_space(path[i]))
			i++;
		if (!path[i])
		{
			home = getenv("HOME");
			if (home)
				chdir(home);
			return ;
		}
		home = path + i;
		if (chdir(home) == -1)
			printf("%s\n", strerror(errno));
	}
}
