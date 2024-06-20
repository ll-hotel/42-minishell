/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 02:47:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

void	ch_exec(t_ch *ch)
{
	int	exit_status;

	if (!ch->cmds.first->next && chooser((t_cmd *)ch->cmds.first, NULL) == 0)
		exit_status = chooser((t_cmd *)ch->cmds.first, ch);
	else
		exit_status = exec_pipeline(ch);
	ch_status_set(exit_status);
}
