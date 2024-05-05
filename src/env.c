/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/05 18:16:08 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(t_env *env, char *const *penv)
{
	t_env_var	*var;
	long		i;

	env->last_return_value = 0;
	env->vars.first = NULL;
	i = 0;
	while (penv[i])
	{
		var = env_var_new(penv[i++]);
		if (!var)
		{
			llst_clear(&env->vars, &env_var_delete);
			return (0);
		}
		llst_addback(&env->vars, (t_llst *)var);
	}
	return (1);
}

void	env_command(char *command, t_env *env)
{
	t_env_var	*vars;

	if (is_void_command(command, "env"))
	{
		vars = (t_env_var *) env->vars.first;
		while (vars->next)
		{
			printf("%s=%s\n",vars->name , vars->value);
			vars = vars->next;
		}
	}
}

void	export(char *command, t_env *env)
{
	char		**var;
	t_env_var	*new_env_var;

	if (is_valid_command(command, "export"))
	{
		write(1, "Debug\n", 6);
		new_env_var = ft_calloc(1, sizeof(t_env_var *));
		*command = *command + 6;
		var = ft_split(command, '=');
		if (var)
		{
			new_env_var->name = ft_strdup(var[0]);
			new_env_var->value = ft_strdup(var[1]);
			// llst_get_last(env->(*vars));
		}
	}
}
