/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/27 18:23:51 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(t_env *env, char *const *penv)
{
	long	i;
	void	*var;

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
		llst_addback(&env->vars, var);
	}
	return (1);
}
