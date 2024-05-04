/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:10:45 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/04 12:11:47 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	is_valid_command(char *full_command, char *command_word)
{
	size_t	size;

	size = ft_strlen(command_word);
	if (!strncmp(full_command, command_word, size))
		if (!full_command[size] || is_space(full_command[size]))
			return (1);
	return (0);
}

short	is_void_command(char *full_command, char *command_word)
{
	size_t	size;

	size = ft_strlen(command_word);
	if (!strncmp(full_command, command_word, size))
		if (!full_command[size])
			return (1);
	return (0);
}

void	chooser(char *command, t_env *env)
{
	if (is_valid_command(command, "echo"))
		echo(command);
	if (is_valid_command(command, "cd"))
		cd(command, env);
	else if (is_valid_command(command, "pwd"))
		pwd(command);
}
