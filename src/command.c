/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:59:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/19 19:04:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_command *command)
{
	if (command)
	{
		ft_free(command->executable);
		ft_free_parray(command->argv);
		ft_free_parray(command->penv);
		if (command->path)
			ft_free(command->path[0]);
		ft_free(command->path);
		ft_bzero(command, sizeof(*command));
		free(command);
	}
}
