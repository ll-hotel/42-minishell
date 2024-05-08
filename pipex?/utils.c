/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:28:11 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/20 17:41:11 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

int	ft_error(char *errmsg)
{
	if (errmsg)
		ft_dprintf(2, "pipex: %s: %s\n", errmsg, strerror(errno));
	else
		ft_dprintf(2, "pipex: %s\n", strerror(errno));
	return (1);
}

void	close_fds(int close_std, int fd0, int fd1)
{
	if (close_std)
	{
		close(0);
		close(1);
		close(2);
	}
	if (fd0 > 0)
		close(fd0);
	if (fd1 > 0)
		close(fd1);
}

void	*ft_free_parray(void **array)
{
	int	i;

	i = -1;
	if (array)
		while (array[++i])
			array[i] = (free(array[i]), NULL);
	return (NULL);
}

void	init_data(t_data *data, char **argv, char **penv)
{
	data->penv = penv;
	data->cmd_args = argv + 2;
	data->path = ft_get_path(penv);
}

int	fd_in_out_error(int *argc, char ***argv, int *fd_in, int *fd_out)
{
	if (fd_in)
	{
		ft_error(argv[0][1]);
		*argc -= 1;
		*argv += 1;
		*fd_in = open("/dev/null", O_RDONLY);
		if (*fd_in == -1)
			return (ft_error("/dev/null"), close_fds(1, -1, -1), 1);
	}
	else if (fd_out)
	{
		ft_error(argv[0][*argc - 1]);
		argv[*argc - 1] = 0;
		*argc -= 1;
		*fd_out = open("/dev/null", O_WRONLY);
		if (*fd_out == -1)
			return (ft_error("/dev/null"), close_fds(1, -1, -1), 1);
	}
	return (0);
}
