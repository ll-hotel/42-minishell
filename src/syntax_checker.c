/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/24 20:40:57 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_one_command(t_token *token);
static int	syntax_error(int token_type);

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
			return (syntax_error(token->type));
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
		while (token && (token->type == TOKEN_REDIR_IN \
					|| token->type == TOKEN_REDIR_OUT))
			token = token->next;
		if (!token)
			return (-1);
		while (token && token->type != TOKEN_PIPE)
		{
			next_command_offset += 1;
			token = token->next;
		}
	}
	return (next_command_offset);
}

static int	syntax_error(int token_type)
{
	char	c;

	c = '|' * (token_type == TOKEN_PIPE) + \
		'<' * (token_type == TOKEN_REDIR_IN) + \
		'<' * (token_type == TOKEN_REDIR_OUT) + \
		'\'' * (token_type == TOKEN_SIMPLE_QUOTE) + \
		'\"' * (token_type == TOKEN_DOUBLE_QUOTE);
	ft_dprintf(2, "minishell: syntax error near token `%c'\n", c);
	return (0);
}
