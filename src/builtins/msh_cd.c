/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:43:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/28 01:36:18 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_command *cmd, t_msh *env)
{
	char		*new_path;
	t_env_var	*home;

	if (cmd->argc > 2)
	{
		perror("too many arguments");
		return (1);
	}
	if (cmd->argc == 1)
	{
		home = env_var_get(env, "HOME");
		if (!home || chdir(home->value) == -1)
			write(2, "miniChell: cd: HOME not set\n", 28);
		return (0);
	}
	new_path = cmd->argv[1];
	if (chdir(new_path) == -1)
	{
		perror(strerror(errno));
		return (1);
	}
	return (0);
}
