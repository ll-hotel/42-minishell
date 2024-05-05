/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:56:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/22 19:57:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_command *cmd, t_env *env)
{
	t_env_var	*vars;

	if (cmd->argc > 1)
		return (0);
	vars = (t_env_var *)env->vars.first;
	while (vars)
	{
		printf("%s=", vars->name);
		if (vars->value)
			printf("%s", vars->value);
		printf("\n");
		vars = vars->next;
	}
	return (0);
}
