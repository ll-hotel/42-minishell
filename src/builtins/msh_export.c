/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/07 21:45:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	insert_evar(t_env_var *evar_head, t_env_var *evar);
static int	env_var_is_valid(char *arg);

int	msh_export(t_command *cmd, t_msh *msh)
{
	t_env_var	*evar;

	evar = env_var_new(cmd->argv[1]);
	if (!evar)
		return (1);
	if (!env_var_is_valid(evar->name))
	{
		ft_dprintf(2, "export: %s: not a valid identifier\n", evar->name);
		env_var_free(evar);
		return (1);
	}
	if (ft_strchr(cmd->argv[1], '='))
	{
		if (!insert_evar((t_env_var *)&msh->env_vars, evar))
			return (1);
	}
	return (0);
}

static int	insert_evar(t_env_var *evar_head, t_env_var *evar)
{
	const int	length = ft_strlen(evar->name) + 1;

	while (evar_head->next && \
			ft_strncmp(evar_head->next->name, evar->name, length))
	{
		evar_head = evar_head->next;
	}
	if (!evar_head->next)
		evar_head->next = evar;
	else if (evar->value)
	{
		ft_free(evar_head->next->value);
		evar_head->next->value = ft_strdup(evar->value);
		if (!evar_head->next->value)
			return (perror("minishell"), 0);
	}
	else
		return (0);
	return (1);
}

static int	env_var_is_valid(char *arg)
{
	size_t	i;

	i = 1;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (ft_isalnum(arg[i]))
		i++;
	if (arg[i])
		return (0);
	return (1);
}
