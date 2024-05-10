/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:45:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/08 18:05:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	free_close_all(char **path, int fd_in, int fd_out)
{
	pipex_close_fds(1, fd_in, fd_out);
	if (path)
	{
		free(*path);
		free(path);
	}
	return (0);
}

static int	open_redirects(t_command *cmd);

int	pipex(t_command *cmd, t_env *env)
{
	int	pid;

#if 0
	cmd->out.fd = open(cmd->argv[cmd->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->out.fd == -1)
		return (pipex_fd_in_out_error(&cmd->argc, &cmd->argv, 0, &cmd->out.fd));
	cmd->in.fd = open(cmd->argv[1], O_RDONLY);
	if (cmd->in.fd == -1)
		return (pipex_fd_in_out_error(&cmd->argc, &cmd->argv, &cmd->in.fd, 0));
#endif
	pid = fork();
	if (pid == -1)
		perror("fork in minishell[pipex]");
	else if (pid == 0)
	{
		cmd->penv = env_to_array(env);
		cmd->path = pipex_get_path(env);
		if (!open_redirects(cmd))
			
		pipex_child(cmd, cmd->path, cmd->fd_in, cmd->fd_out);
	}
	else
		waitpid(-1, NULL, 0);
	pipex_close_fds(1, cmd->fd_in, cmd->fd_out);
	ft_free_parray(cmd->argv);
	return (pid >= 0);
}

static int	re_open(t_file *file, int *last_in, int *last_out)
{
	if (file->way == REDIRECT_IN)
	{
		if (last_in)
			ft_close(*last_in);
		file->fd = open(file->name, O_RDONLY);
	}
	else
	{
		if (last_out)
			ft_close(*last_out);
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (file->fd < 0)
	{
		perror(file->name);
		return (0);
	}
	return (1);
}

void	file_delete(t_file *file)
{
	if (!file)
		return ;
	file->name = ft_free(file->name);
	file->fd = ft_close(file->fd);
	free(file);
}

static int	open_redirects(t_command *cmd)
{
	t_llst_head	*files;

	files = &cmd->redirections;
	if (!files->first)
		return (0);
	while (files->first->next)
	{
		if (!re_open((t_file *)files->first, &cmd->fd_in, &cmd->fd_out))
			break ;
		llst_delone(files, (void *)&file_delete);
	}
	if (!re_open((t_file *)files->first, &cmd->fd_in, &cmd->fd_out))
	{
		perror(((t_file *)files->first)->name);
		llst_delone(files, (void *)&file_delete);
		return (1);
	}
	return (0);
}
