/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:53:03 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/27 22:34:01 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_command *cmd, t_env *env)
{
	t_env_var	*vars;
	t_env_var	*previous_vars;

	previous_vars = NULL;
	if (cmd->argc < 2)
		return (0);
	vars = (t_env_var *) env->vars.first;
	while (vars && ft_strncmp(vars->name, cmd->argv[1], \
		ft_strlen(cmd->argv[1])))
	{
		previous_vars = vars;
		vars = vars->next;
	}
	if (vars)
		llst_delone((void *) previous_vars, env_var_free);
	return (0);
}
