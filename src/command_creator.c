/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/02 14:58:38 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	argv_count(t_vec *vec_argv);

void	*command_creator(t_token *token)
{
	t_command	*command;
	t_vec		vec_argv;

	command = ft_calloc(1, sizeof(*command));
	if (!command)
		return (NULL);
	ft_bzero(command, sizeof(*command));
	vec_new(&vec_argv, sizeof(char *));
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			if (!vec_addback(&vec_argv, token->str))
				return (free(command), NULL);
		}
		token = token->next;
	}
	command->argc = argv_count(&vec_argv);
	command->argv = ft_calloc(command->argc + 1, sizeof(*command->argv));
	if (!command->argv)
		return (free(command), NULL);
	ft_memmove(command->argv, vec_argv.array, \
			command->argc * sizeof(*command->argv));
	return (command);
}

static int	argv_count(t_vec *vec_argv)
{
	int	count;

	count = 0;
	while (vec_at(vec_argv, count) && *(char **)vec_at(vec_argv, count))
		count += 1;
	return (count);
}
