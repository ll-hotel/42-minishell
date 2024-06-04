/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:53:03 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/03 19:34:49 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_command *cmd, t_msh *msh)
{
	t_env_var	*vars;
	t_llst_head	*previous_vars;

	previous_vars = &msh->env_vars;
	if (cmd->argc < 2)
		return (0);
	vars = (t_env_var *)msh->env_vars.first;
	while (vars && ft_strncmp(vars->name, cmd->argv[1], \
		ft_strlen(cmd->argv[1])))
	{
		previous_vars = (t_llst_head *) previous_vars->first;
		vars = vars->next;
	}
	if (vars)
		llst_delone((void *) previous_vars, env_var_free);
	return (0);
}
