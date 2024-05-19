/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipex_forked.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:25:16 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/19 19:23:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_delete(t_file *file);
static int	open_redirects(t_command *cmd);
static int	re_open(t_file *file, int *last_in, int *last_out);

int	pipex_forked(t_command *cmd, t_env *env)
{
	env->last_return_value = I_AM_CHILD;
	if (open_redirects(cmd) == RET_ERROR)
		return (RET_ERROR);
	cmd->penv = env_to_array(env);
	printf("CHILD  -  penv: %p\n", cmd->penv);
	cmd->path = pipex_get_path(env);
	printf("CHILD  -  path: %p\n", cmd->path);
	if (pipex_find_command(cmd, cmd->path) == RET_ERROR)
		return (RET_ERROR);
	if (cmd->fd_in >= 0)
	{
		if (dup2(cmd->fd_in, 0))
			return (perror("dup2"), RET_ERROR);
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
	{
		if (dup2(cmd->fd_out, 1))
			return (perror("dup2"), RET_ERROR);
		close(cmd->fd_out);
	}
	return (execve(cmd->executable, cmd->argv, cmd->penv));
}

static int	open_redirects(t_command *cmd)
{
	t_llst_head	*files;

	files = &cmd->redirections;
	if (!files->first)
		return (1);
	while (files->first->next)
	{
		if (!re_open((t_file *)files->first, &cmd->fd_in, &cmd->fd_out))
		{
			perror(((t_file *)files->first)->name);
			break ;
		}
		llst_delone(files, (void *)&file_delete);
	}
	if (!re_open((t_file *)files->first, &cmd->fd_in, &cmd->fd_out))
	{
		perror(((t_file *)files->first)->name);
		llst_delone(files, (void *)&file_delete);
		return (0);
	}
	return (1);
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
