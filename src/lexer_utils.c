/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/04 15:35:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int c)
{
	return (c == '$' \
			|| c == '\'' || c == '\"' \
			|| c == '|' || c == '<' || c == '>');
}

t_token	*lexer_word(char *str, int *i, char single_quoted)
{
	const int	start = *i;
	char		*tmp;

	if (single_quoted)
		while (str[*i] && str[*i] != '\'')
			*i += 1;
	else
		while (str[*i] && !is_operator(str[*i]))
			*i += 1;
	tmp = ft_substr(str, start, *i - start);
	if (tmp)
		return (token_new(tmp, TOKEN_WORD));
	return (NULL);
}

t_token	*lexer_operator(char *str, int *i)
{
	char const	op = str[(*i)++];
	char		*tmp;

	if (op == '$')
		return (token_new(NULL, TOKEN_DOLLAR));
	else if (op == '\'')
		return (token_new(NULL, TOKEN_SIMPLE_QUOTE));
	else if (op == '\"')
		return (token_new(NULL, TOKEN_DOUBLE_QUOTE));
	else if (op == '|')
		return (token_new(NULL, TOKEN_PIPE));
	else if (op == '<' || op == '>')
	{
		tmp = ft_substr(&op, 0, 1);
		if (tmp)
			return (token_new(tmp, TOKEN_REDIRECT));
	}
	return (NULL);
}
