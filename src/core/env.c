/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/07 21:54:53 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_shlvl(char *old_value);

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
		if (ft_strncmp(var->name, "SHLVL", 6) == 0)
			var->value = get_shlvl(var->value);
	}
	return (1);
}

static char	*get_shlvl(char *old_value)
{
	char	*tmp;

	if (!old_value || !ft_is_number(old_value))
	{
		tmp = ft_strdup("1");
	}
	else
		tmp = ft_itoa(ft_atoi(old_value) + 1);
	if (old_value)
		free(old_value);
	return (tmp);
}
