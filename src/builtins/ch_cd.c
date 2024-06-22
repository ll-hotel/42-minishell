/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:43:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/22 20:57:01 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	set_evar_value(t_ch *ch, char *name, char *value);
static int	refresh_pwd(t_ch *ch, char *old_pwd);
static int	chdir_cd(t_ch *ch, t_cmd *cmd, char **new_pwd);

int	ch_cd(t_cmd *cmd, t_ch *ch)
{
	char	*old_pwd;
	char	*new_pwd;

	if (cmd->argc > 2)
		return (write(2, "miniChell: too many arguments\n", 30), 1);
	old_pwd = get_pwd(ch);
	if (old_pwd == NULL)
		return (perror("cd"), 1);
	if (chdir_cd(ch, cmd, &new_pwd))
		return (1);
	if (refresh_pwd(ch, old_pwd))
		return (1);
	return (0);
}

static int	chdir_cd(t_ch *ch, t_cmd *cmd, char **new_pwd)
{
	t_evar	*home;

	if (cmd->argc == 1)
	{
		home = find_evar(ch, "HOME");
		if (home == NULL || !home->value)
		{
			write(2, "miniChell: cd: HOME not set\n", 18);
			return (1);
		}
		*new_pwd = home->value;
	}
	else
		*new_pwd = cmd->argv[1];
	if (chdir(*new_pwd) == -1)
	{
		ft_dprintf(2, "miniChell: cd: `%s': %s\n", *new_pwd, strerror(errno));
		return (1);
	}
	return (0);
}

static int	refresh_pwd(t_ch *ch, char *old_pwd)
{
	char	*new_pwd;

	if (set_evar_value(ch, "OLDPWD", old_pwd))
		return (1);
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("miniChell: cd: error retrieving current directory");
		return (1);
	}
	if (set_evar_value(ch, "PWD", new_pwd))
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}

static int	set_evar_value(t_ch *ch, char *name, char *value)
{
	t_evar	*evar;

	evar = find_evar(ch, name);
	if (evar)
	{
		ft_free(evar->value);
		evar->value = ft_strdup(value);
		if (!evar->value)
		{
			perror("miniChell: cd");
			return (1);
		}
		return (0);
	}
	evar = evar_new(name);
	if (evar)
		evar->value = ft_strdup(value);
	if (!evar || !evar->value)
	{
		perror("miniChell: cd");
		return (1);
	}
	return (0);
}
