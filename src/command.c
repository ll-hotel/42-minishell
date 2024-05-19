/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:59:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/18 16:59:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_command *command)
{
	if (!command)
		return ;
	ft_free(command->executable);
	ft_free_parray(command->argv);
	ft_free_parray(command->penv);
	//ft_free_parray(command->path);
	free(command);
}
