/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:56:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 22:00:16 by ll-hotel         ###   ########.fr       */
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
		printf("%s=", vars->name);
		if (vars->value)
			printf("%s", vars->value);
		printf("\n");
		vars = vars->next;
	}
	return (0);
}
