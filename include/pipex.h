/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:12:12 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/18 16:16:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "minishell.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <wait.h>

enum	e_return_status
{
	RET_ERROR = 0,
	RET_NICE = 1
};

int		pipex(t_command *cmd, t_env *env);
int		pipex_forked(t_command *cmd, t_env *env);

int		pipex_child(t_command *cmd, char **path, int input, int output);
int		pipex_exec(t_command *cmd, char **path, int input, int output);
void	*pipex_free_parray(void **array);
char	**pipex_get_path(t_env *env);
int		pipex_find_command(t_command *cmd, char **path);
int		pipex_error(char *errmsg);
void	pipex_close_fds(int close_std, int fd0, int fd1);
int		pipex_fd_in_out_error(int *argc, char ***argv, int *fd_in, int *fd_out);

#endif
