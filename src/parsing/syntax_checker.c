/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 04:51:29 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_one_command(t_token *token);

int	syntax_checker(t_token *token)
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
		if (!token)
			continue ;
		if (token->type == TOKEN_PIPE && \
				token->next && token->next->type == TOKEN_PIPE)
			return (msh_syntax_err('|'), 0);
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
		while (token && token->type != TOKEN_PIPE)
		{
			while (token && (token->type == TOKEN_REDIR_IN \
						|| token->type == TOKEN_REDIR_OUT))
			{
				next_command_offset += 1;
				token = token->next;
			}
			if (!token)
				return (-1);
			while (token && token->type == TOKEN_WORD)
			{
				next_command_offset += 1;
				token = token->next;
			}
			if (token && token->type != TOKEN_PIPE && token->type != TOKEN_REDIR_IN && \
					token->type != TOKEN_REDIR_OUT)
				return (-1);
		}
	}
	return (next_command_offset);
}
