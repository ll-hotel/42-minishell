/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:56:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 01:39:45 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

int	ch_env(t_cmd *cmd, t_ch *ch)
{
	t_evar	*vars;

	if (cmd->argc > 1)
		return (0);
	vars = (t_evar *)ch->evars.first;
	while (vars)
	{
		if (vars->value)
			printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
	return (0);
}
