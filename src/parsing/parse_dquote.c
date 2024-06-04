/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:56:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/30 02:56:32 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_dquote(t_token *head, t_msh *env)
{
	t_token	*subtoken;
	char	*joined;

	subtoken = (t_token *)head->next->inner_tokens.first;
	if (!subtoken)
		return (0);
	while (subtoken->next)
	{
		if (subtoken->next->type == TOKEN_ENV_VAR && \
				!env_var_expand((t_llst_head *)subtoken, env))
			return (0);
		joined = ft_strjoin(subtoken->str, subtoken->next->str);
		subtoken->str = ft_free(subtoken->str);
		if (!joined)
			return (0);
		subtoken->str = joined;
		llst_delone((t_llst_head *)subtoken, token_free);
	}
	joined = subtoken->str;
	subtoken->str = NULL;
	token_free(subtoken);
	head->next->str = joined;
	head->next->type = TOKEN_WORD;
	return (1);
}
