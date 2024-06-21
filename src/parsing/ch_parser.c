/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:46:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/03 06:35:21 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	parser_remove_spaces(t_token *head);

int	ch_parser(t_llst_head *token_lst, t_ch *ch)
{
	if (!expand_evars((t_token *)token_lst, ch))
		return (0);
	if (!check_redir_validity((t_token *)token_lst))
		return (0);
	if (!split_evars((t_token *)token_lst))
		return (0);
	if (!parser_remove_spaces((t_token *)token_lst))
		return (0);
	parse_redir((t_token *)token_lst);
	if (!parser_heredoc((t_token *)token_lst, ch))
		return (0);
	return (1);
}

static int	parser_remove_spaces(t_token *head)
{
	char	*joined;

	while (head->next)
	{
		if (head->next->type == TOKEN_SPACE)
			llst_delone((t_llst_head *)head, token_free);
		else if (head->next->type == TOKEN_WORD)
		{
			while (head->next->next && head->next->next->type == TOKEN_WORD)
			{
				joined = ft_strjoin(head->next->str, head->next->next->str);
				if (!joined)
					return (0);
				free(head->next->str);
				head->next->str = joined;
				llst_delone((t_llst_head *)head->next, token_free);
			}
			head = head->next;
		}
		else
			head = head->next;
	}
	return (1);
}
