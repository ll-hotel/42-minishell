/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 02:51:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(t_msh *msh, char *const *envp)
{
	t_env_var	*var;
	long		i;

	i = 0;
	while (envp[i])
	{
		var = env_var_new(envp[i++]);
		if (!var)
		{
			llst_clear(&msh->env_vars, &env_var_free);
			return (0);
		}
		llst_addback(&msh->env_vars, (t_llst *)var);
	}
	return (1);
}
