/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammary_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/24 20:27:29 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_one_command(t_token *token);

int	grammary_checker(t_token *token)
{
	int	next_command_offset;

	if (!token)
		return (0);
	next_command_offset = check_for_one_command(token);
	while (next_command_offset > 0)
	{
		while (next_command_offset > 0)
		{
			next_command_offset -= 1;
			token = token->next;
		}
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
		next_command_offset = check_for_one_command(token);
	}
	return (next_command_offset == 0);
}

static int	check_for_one_command(t_token *token)
{
	int	next_command_offset;

	next_command_offset = 0;
	if (token)
	{
		if (token->type == TOKEN_SPACE)
		{
			token = token->next;
			next_command_offset += 1;
		}
		if (token && token->type != TOKEN_WORD && token->type != TOKEN_SIMPLE_QUOTE && \
				token->type != TOKEN_DOUBLE_QUOTE)
			return (-1);
		while (token && token->type != TOKEN_PIPE)
		{
			token = token->next;
			next_command_offset += 1;
		}
	}
	return (next_command_offset);
}
