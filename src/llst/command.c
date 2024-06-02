/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:59:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 15:35:29 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(void *command)
{
	t_command *const	cmd = command;

	if (cmd)
	{
		ft_close(cmd->fd_in);
		ft_close(cmd->fd_out);
		ft_free(cmd->executable);
		llst_clear(&cmd->redirects, free);
		ft_free_parray(cmd->argv);
		ft_free_parray(cmd->envp);
		if (cmd->path)
			ft_free(cmd->path[0]);
		ft_free(cmd->path);
		ft_bzero(cmd, sizeof(*cmd));
		free(cmd);
	}
}
