/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/08 09:42:00 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(char *command, t_env *env)
{
	t_env_var	*new_env_var;
	t_env_var	*vars;

	if (is_valid_command(command, "export") && ft_strchr(command, '='))
	{
		command = command + 7;
		new_env_var = env_var_new(command);
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
				malloc_checker(vars->value);
			}
		}
	}
}
