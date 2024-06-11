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

int	set_evar_value(t_msh *env, char *name, char *value);

int	msh_cd(t_command *cmd, t_msh *env)
{
	char		*new_path;
	t_env_var	*home;
	int			test;
	char		*old_path;

	if (cmd->argc > 2)
	{
		write(2, "miniChell: too many arguments\n", 30);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
	{
		perror("cd");
		return (1);
	}
	if (cmd->argc == 1)
	{
		home = env_var_get(env, "HOME");
		if (home == NULL || chdir(home->value) == -1)
		{
			write(2, "cd: HOME not set\n", 18);
			ft_free(old_path);
			return (1);
		}
	}
	else
	{
		new_path = cmd->argv[1];
		test = chdir(new_path);
		if (test == -1)
		{
			ft_free(old_path);
			perror("cd");
			return (1);
		}
	}
	set_evar_value(env, "OLDPWD", old_path);
	new_path = getcwd(NULL, 0);
	set_evar_value(env, "PWD", new_path);
	free(old_path);
	free(new_path);
	return (0);
}

char	*free_to_join(char *str1, char *str2)
{
	char	*temp;
	temp = ft_strdup(str1);
	if (temp == NULL)
		return (NULL);
	free(str1);
	str1 = ft_strjoin(temp, str2);
	free(temp);
	return (str1);
}

int	set_evar_value(t_msh *env, char *name, char *value)
{
	t_env_var	*evar;

	evar = env_var_get(env, name);
	if (evar == NULL)
	{
		name = free_to_join(name, "=");
		if (name == NULL)
		{
			perror("cd");
			return (1);
		}
		evar = env_var_new(name);
	}
	ft_free(evar->value);
	evar->value = ft_strdup(value);
	if (evar->value == NULL)
	{
		perror("cd");
		return (1);
	}
	return (0);
}