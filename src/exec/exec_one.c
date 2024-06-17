/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:25:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/06 16:33:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

int	exec_one(t_ch *ch, t_cmd *cmd)
{
	int	status;

	if (exec_open_redirs(cmd) != 0)
		ch_exit(ch, 1);
	if (!cmd->argv || !cmd->argv[0])
		ch_exit(ch, 0);
	cmd->envp = ch_to_array((t_evar *)ch->evars.first);
	cmd->path = exec_get_path(ch);
	status = exec_find_cmd(cmd, cmd->path);
	if (status != 0)
	{
		ft_close(cmd->fd_in);
		ft_close(cmd->fd_out);
		ch_exit(ch, status);
	}
	if (exec_dup2(cmd) != 0)
		return (errno);
	return (execve(cmd->executable, cmd->argv, cmd->envp));
}
