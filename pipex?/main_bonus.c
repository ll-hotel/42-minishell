/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/20 20:03:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	free_close_all(char **path, int fd_in, int fd_out)
{
	close_fds(1, fd_in, fd_out);
	if (path)
	{
		free(*path);
		free(path);
	}
	return (0);
}

int	main(int argc, char **argv, char **penv)
{
	t_data	data;
	int		fd_in;
	int		fd_out;
	int		pid;

	if (argc < 5)
		return (ft_dprintf(2, "Usage: pipex file1 cmd1 cmd2 [cmd3..] file2\n"),
			close_fds(1, -1, -1), 1);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1 && fd_in_out_error(&argc, &argv, 0, &fd_out))
		return (1);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1 && fd_in_out_error(&argc, &argv, &fd_in, 0))
		return (1);
	init_data(&data, argv, penv);
	pid = fork();
	if (pid == -1)
		return (close_fds(1, fd_in, fd_out), free(data.path), ft_error("fork"),
			1);
	else if (pid == 0)
		process_child(&data, argc - 3, fd_in, fd_out);
	else
		waitpid(-1, NULL, 0);
	return (free_close_all(data.path, fd_in, fd_out));
}
