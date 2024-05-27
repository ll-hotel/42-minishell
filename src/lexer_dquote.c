/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:09:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 05:56:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*sub_word(char *line, int *p_i);

t_token	*lexer_dquote(char *line, int *p_i)
{
	t_token		*dq_token;
	t_token		*w;
	int			i;

	dq_token = token_new(NULL, TOKEN_DQUOTE);
	if (!dq_token)
		return (NULL);
	i = 0;
	if (!ft_strchr(line, '\"'))
		return (token_free(dq_token), msh_syntax_err(-'\"'), NULL);
	while (line[i])
	{
		if (line[i] == '$')
			w = lexer_dollar(line + i + 1, p_i);
		else
			w = sub_word(line + i, p_i);
		i += *p_i;
		if (!w)
			return (token_free(dq_token), NULL);
		llst_addback(&dq_token->inner_lst, (t_llst *)w);
	}
	*p_i = i + 1;
	return (dq_token);
}

static t_token	*sub_word(char *line, int *p_i)
{
	int		limit;
	int		i;
	char	*s;

	limit = ft_strichr(line, '\"');
	if (!line[limit])
		return (msh_syntax_err(0), NULL);
	i = ft_strichr(line, '$');
	*p_i = ft_min(i, limit);
	s = ft_substr(line, 0, *p_i);
	if (s)
		return (token_new(s, TOKEN_WORD));
	return (NULL);
}
