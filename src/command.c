/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:59:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/04 16:49:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(void *command)
{
	if (!command)
		return ;
	free_array((void **)((t_command *)command)->argv);
	((t_command *)command)->argv = NULL;
	free(command);
}
