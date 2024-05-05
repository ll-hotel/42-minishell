/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:30:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/21 12:31:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_exec(t_data *data, int fd_in, int fd_out)
{
	char	**command;

	command = ft_find_command(data->path, data->cmd_args[0]);
	if (!command || dup2(fd_in, 0) == -1 || dup2(fd_out, 1) == -1)
		return (close_fds(0, fd_in, fd_out), 1);
	close_fds(0, fd_in, fd_out);
	return (execve(command[0], command, data->penv));
}

int	process_child(t_data *data, int len, int fd_in, int fd_out)
{
	int		pip[2];
	int		pid2;

	if (len < 1)
		return (close_fds(1, fd_in, fd_out), 1);
	if (len == 1)
		return (process_exec(data, fd_in, fd_out));
	if (pipe(pip) == -1)
		return (ft_error("pipe"));
	pid2 = fork();
	if (pid2 == -1)
		return (close_fds(0, pip[0], pip[1]), close_fds(0, fd_in, fd_out), \
				ft_error("fork in child"), 1);
	else if (pid2)
		return (close_fds(0, pip[0], fd_out), \
				process_exec(data, fd_in, pip[1]));
	data->cmd_args += 1;
	return (close_fds(0, pip[1], fd_in), \
			process_child(data, len - 1, pip[0], fd_out));
}
