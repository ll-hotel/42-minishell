/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:28:11 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/18 16:29:08 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_close_fds(int close_std, int fd0, int fd1)
{
	if (close_std)
	{
		close(0);
		close(1);
		close(2);
	}
	ft_close(fd0);
	ft_close(fd1);
}

void	*pipex_free_parray(void **array)
{
	int	i;

	i = -1;
	if (array)
		while (array[++i])
			array[i] = ft_free(array[i]);
	return (NULL);
}

int pipex_error(char *errmsg)
{
	perror(errmsg);
	return (0);
}
