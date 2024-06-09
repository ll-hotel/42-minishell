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
	t_env_var	*FF;
	int			test;
	char		*old_path;

	if (cmd->argc > 2)
	{
		write(2, "miniChell: too many arguments\n", 30);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (cmd->argc == 1)
	{
		home = env_var_get(env, "HOME");
		if (!home || chdir(home->value) == -1)
		{
			write(2, "cd: HOME not set\n", 18);
			return (1);
		}
	}
	else
	{
		new_path = cmd->argv[1];
		test = chdir(new_path);
		if (test == -1)
		{
			perror("cd");
			return (1);
		}
	}
	FF = (t_env_var *) env->env_vars.first;
	while (ft_strncmp("OLDPWD",FF->name, 7))
	{
		FF = FF->next;
	}
	FF->value = strdup(old_path);
	FF = (t_env_var *) env->env_vars.first;
	while (ft_strncmp("PWD",FF->name, 4))
	{
		FF = FF->next;
	}
	FF->value = strdup(getcwd(NULL,0));
	return (0);
}

