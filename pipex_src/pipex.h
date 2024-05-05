/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:12:12 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/20 17:41:30 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <wait.h>

typedef struct s_data
{
	char	**cmd_args;
	char	**penv;
	char	**path;
}	t_data;

int		process_child(t_data *data, int len, int input, int output);
int		process_exec(t_data *data, int input, int output);
void	*ft_free_parray(void **array);
char	**ft_get_path(char **penv);
char	**ft_find_command(char **path, char *arg);
int		ft_error(char *errmsg);
void	close_fds(int close_std, int fd0, int fd1);
void	init_data(t_data *data, char **argv, char **penv);
int		fd_in_out_error(int *argc, char ***argv, int *fd_in, int *fd_out);
#endif
