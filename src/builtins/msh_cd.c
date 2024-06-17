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

int	set_evar_value(t_msh *msh, char *name, char *value);
int	refresh_pwd(t_msh *env, char *old_path, char *new_path);
int	chdir_cd(t_msh *msh, t_command *cmd, char *old_path, char *new_path);

int	msh_cd(t_command *cmd, t_msh *msh)
{
	char		*new_path;
	char		*old_path;

	new_path = NULL;
	if (cmd->argc > 2)
		return (write(2, "miniChell: too many arguments\n", 30), 1);
	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
		return (perror("cd"), 1);
	if (chdir_cd(msh, cmd, old_path, new_path))
		return (1);
	if (refresh_pwd(msh, old_path, new_path))
		return (1);
	return (0);
}

int	chdir_cd(t_msh *msh, t_command *cmd, char *old_path, char *new_path)
{
	t_env_var	*home;
	int			test;

	if (cmd->argc == 1)
	{
		home = env_var_get(msh, "HOME");
		if (home == NULL || chdir(home->value) == -1)
		{
			ft_free(old_path);
			return (write(2, "cd: HOME not set\n", 18), 1);
		}
	}
	else
	{
		new_path = cmd->argv[1];
		test = chdir(new_path);
		if (test == -1)
		{
			ft_free(old_path);
			return (perror("cd"), 1);
		}
	}
	return (0);
}

int	refresh_pwd(t_msh *env, char *old_path, char *new_path)
{
	if (set_evar_value(env, "OLDPWD", old_path))
		return (1);
	new_path = getcwd(NULL, 0);
	if (new_path == NULL)
		return (1);
	if (set_evar_value(env, "PWD", new_path))
		return (1);
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

int	set_evar_value(t_msh *msh, char *name, char *value)
{
	t_env_var	*evar;

	evar = env_var_get(msh, name);
	if (evar == NULL)
	{
		name = free_to_join(name, "=");
		if (name == NULL)
		{
			perror("cd");
			return (1);
		}
		evar = env_var_new(name);
		if (evar == NULL)
			return (0);
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
