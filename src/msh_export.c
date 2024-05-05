/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/22 20:12:28 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_export(t_command *cmd, t_env *env)
{
	t_env_var	*new_env_var;
	t_env_var	*vars;

	if (ft_strchr(cmd->argv[1], '='))
	{
		new_env_var = env_var_new(cmd->argv[1]);
		vars = (t_env_var *) env->vars.first;
		while (vars && ft_strncmp(vars->name, new_env_var->name, \
			ft_strlen(new_env_var->name)))
			vars = vars->next;
		if (!vars)
			llst_addback(&env->vars, (t_llst *) new_env_var);
		else
		{
			if (new_env_var->value)
			{
				ft_free(vars->value);
				vars->value = ft_strdup(new_env_var->value);
				if (!vars->value)
					return (perror("minishell"), 1);
			}
		}
	}
	return (0);
}
