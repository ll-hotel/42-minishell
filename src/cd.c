/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:43:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/04 12:13:56 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *command, t_env *env)
{
	char		*new_path;
	t_env_var	*home;

	if (!ft_strncmp(command, "cd", 2))
	{
		if (is_void_command(command, "cd"))
		{
			home = env_var_get(env, "HOME");
			if (home->value)
				chdir(home->value);
			return ;
		}
		new_path = command + 3;
		if (chdir(new_path) == -1)
			printf("%s\n", strerror(errno));
	}
}
