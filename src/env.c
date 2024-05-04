/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/04 15:16:11 by ll-hotel         ###   ########.fr       */
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
