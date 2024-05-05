/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/22 19:56:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(t_env *env, char *const *envp)
{
	t_env_var	*var;
	long		i;

	i = 0;
	while (envp[i])
	{
		var = env_var_new(envp[i++]);
		if (!var)
		{
			llst_clear(&env->vars, &env_var_free);
			return (0);
		}
		llst_addback(&env->vars, (t_llst *)var);
	}
	return (1);
}

void	free_env(t_env *env)
{
	t_env_var	*vars;

	vars = (t_env_var *) env->vars.first;
	while (vars)
	{
		vars->name = ft_free(vars->name);
		vars->value = ft_free(vars->value);
		vars = vars->next;
	}
}
