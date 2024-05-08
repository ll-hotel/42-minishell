/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:53:03 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/08 08:16:27 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_unset(char *command, t_env *env)
{
	t_env_var	*vars;
	t_env_var	*previous_vars;

	command = command + 6;
	previous_vars = NULL;
	vars = (t_env_var *) env->vars.first;
	while (vars && ft_strncmp(vars->name, command, \
		ft_strlen(command)))
	{
		previous_vars = vars;
		vars = vars->next;
	}
	if (vars)
		llst_delone((void *) previous_vars, env_var_delete);
}
