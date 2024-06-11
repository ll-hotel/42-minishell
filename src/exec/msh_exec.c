/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:45 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_exec(t_msh *msh)
{
	pid_t	pid;
	int		exit_status;

	pid = 0;
	if (!msh->cmds.first->next && chooser((t_command *)msh->cmds.first, NULL) == 0)
		exit_status = chooser((t_command *)msh->cmds.first, msh);
	else
		exit_status = exec_pipeline(msh);
	msh_status_set(exit_status);
}
