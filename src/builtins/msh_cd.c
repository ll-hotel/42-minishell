/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:43:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/06 16:21:35 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_command *cmd, t_msh *env)
{
	char		*new_path;
	t_env_var	*home;
	int			test;

	if (cmd->argc > 2)
	{
		write(2, "miniChell: too many arguments\n", 30);
		return (1);
	}
	if (cmd->argc == 1)
	{
		home = env_var_get(env, "HOME");
		if (!home || chdir(home->value) == -1)
		{
			write(2, "cd: HOME not set\n", 18);
			return (1);
		}
		return (0);
	}
	new_path = cmd->argv[1];
	test = chdir(new_path);
	if (test == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

void	refresh_pwd(void)
{
	t_command	truc;

	truc.argv = ft_calloc(3, sizeof(char *));
	truc.argv[1] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	truc.argv[2] = NULL;
}
