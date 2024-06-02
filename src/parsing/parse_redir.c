/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:52:53 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/02 23:27:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(t_token *head)
{
	while (head->next)
	{
		if (head->next->type == TOKEN_REDIR_IN || \
			head->next->type == TOKEN_REDIR_OUT)
		{
			head->next->str = head->next->next->str;
			head->next->next->str = NULL;
			llst_delone((t_llst_head *)head->next, token_free);
		}
		head = head->next;
	}
}

int	check_redir_validity(t_token *head)
{
	t_token	*tok;

	tok = head->next;
	while (tok)
	{
		if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT)
		{
			if (tok->next->type == TOKEN_SPACE)
				tok = tok->next;
			if (tok && tok->next && tok->next->type == TOKEN_ENV_VAR && \
					(ft_strchr(tok->next->str, ' ') || \
					ft_strchr(tok->next->str, '\t')))
			{
				ft_dprintf(2, "minishell: %s: ambiguous redirect\n", \
						tok->next->str);
				return (0);
			}
		}
		tok = tok->next;
	}
	return (1);
}
